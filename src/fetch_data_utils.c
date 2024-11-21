#include "fetch_data_utils.h"
#include "memory_utils.h"
#include "latency_utils.h"
#include "json_utils.h"
#include "server_utils.h"
#include <curl/curl.h>
#include <process.h>


/**
 * @brief Thread-safe wrapper for fetching and sending data using CURL.
 *
 * This function runs in its own thread and performs the following:
 * 1. Constructs a URL with query parameters.
 * 2. Fetches data from the URL using CURL.
 * 3. Parses the JSON response to extract specific fields (e.g., current price).
 * 4. Sends the extracted data to the server asynchronously.
 *
 * @param param A pointer to a CURL object initialized by the caller.
 * @return Returns 0 upon completion.
 */
unsigned int __stdcall fetchAndSendDataThread(void* param) {
    // Cast the input parameter to a CURL pointer
    CURL* curl = (CURL*)param;

    // Initialize a buffer for storing fetched data
    MemoryBuffer readBuffer = {0};
    CURLcode res;
    
    // Construct the URL for the HTTP reque
    char url[BUFFER_SIZE];
    snprintf(url, sizeof(url), "%s?symbol=%s&token=%s", BASE_URL, SYMBOL, API_KEY);

    // Set CURL options for the request
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

    // Perform the CURL request
    res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
    } else {
        // Parse and extract the "current price" field from the JSON response
        const char* currentPrice = extractValueUsingJansson(readBuffer.data, "c");
        printf("Current Price (ticker: %s): %s\n", SYMBOL, currentPrice);

        // Send the extracted data to the server asynchronously
        asyncSendToServer(currentPrice);
    }

    // Free the memory buffer
    free(readBuffer.data);

    return 0;
}


/**
 * @brief Asynchronously fetch and send data in a new thread.
 *
 * This function creates a new thread to execute the `fetchAndSendDataThread` function.
 * The thread is detached, so the main program does not wait for its completion.
 *
 * @param curl A pointer to a CURL object initialized by the caller.
 */
void asyncFetchAndSendData(CURL* curl) {
    // Launch the `fetchAndSendDataThread` function in a new thread
    HANDLE thread = (HANDLE)_beginthreadex(NULL, 0, fetchAndSendDataThread, (void*)curl, 0, NULL);

    // Close the thread handle immediately; no need to join
    CloseHandle(thread);
}


/**
 * @brief Periodically fetch data and measure latency.
 *
 * This function runs an infinite loop that:
 * 1. Waits until the start of the next interval (e.g., next minute).
 * 2. Starts a latency measurement timer.
 * 3. Calls `asyncFetchAndSendData` to fetch stock data asynchronously.
 *
 * @param curl A pointer to a CURL object initialized by the caller.
 */
void fetchSendWait(CURL* curl) {
    while (1) {
        // Get the current time
        time_t now = time(NULL);
        struct tm* localTime = localtime(&now);

        // Calculate the time (in seconds) until the next interval
        int secondsToWait = (INTERVAL_M - 1) * 60 + (60 - localTime->tm_sec);

        // Sleep until the next interval (convert seconds to milliseconds)
        Sleep(secondsToWait * 1000);

        // Start latency measurement
        start_latency_measurement();

        // Fetch and send stock data asynchronously
        asyncFetchAndSendData(curl);
    }
}
