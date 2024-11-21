#include "server_utils.h"
#include "latency_utils.h"
#include <winsock2.h>
#include <process.h>
#include <stdio.h>
#include <time.h>


/**
 * @brief Sends data to a server running on localhost.
 *
 * This function establishes a TCP connection to a server at `127.0.0.1:8080`
 * and sends the specified data. It handles socket creation, connection, and
 * cleanup. In case of errors, appropriate messages are logged.
 *
 * @param data A pointer to the data to be sent.
 */
void sendToServer(const char* data) {
    WSADATA wsa;
    SOCKET s;
    struct sockaddr_in server;
    const char* request_format = "POST / HTTP/1.1\r\n"
                                 "Host: 127.0.0.1:8080\r\n"
                                 "Content-Type: application/x-www-form-urlencoded\r\n"
                                 "Content-Length: %zu\r\n\r\n"
                                 "value=%s";

    // Initialize Winsock
    if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
        printf("Failed. Error Code : %d\n", WSAGetLastError());
        return;
    }

    // Create socket
    if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d\n", WSAGetLastError());
        return;
    }

    // Configure server address
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(8080);

    // Connect to server
    if (connect(s, (struct sockaddr*)&server, sizeof(server)) < 0) {
        printf("Connection failed with error code : %d\n", WSAGetLastError());
        closesocket(s);
        WSACleanup();
        return;
    }

    // Calculate the Content-Length based on the length of the data
    int content_length = strlen(data) + 6; // "value=" is 6 characters long

    // Format the HTTP request with the data
    char request[1024];  // Ensure the buffer is large enough to hold the formatted request
    snprintf(request, sizeof(request), request_format, content_length, data);

    // Send the HTTP reques
    if (send(s, request, strlen(request), 0) < 0) {
        printf("Send failed with error code : %d\n", WSAGetLastError());
    }

    // Close socket and cleanup
    closesocket(s);
    WSACleanup();
}


/**
 * @brief Thread-safe wrapper for the `sendToServer` function.
 *
 * This function runs in a separate thread and calls `sendToServer` to send
 * data. After the data is sent, it calculates and reports latency.
 *
 * @param param A pointer to the data to be sent (must be a dynamically allocated string).
 * @return Always returns 0 upon completion.
 */
unsigned int __stdcall sendToServerThread(void* param) {
    const char* data = (const char*)param;

    // Send the data to the server
    sendToServer(data);

    // Calculate and report latency
    end_latency_measurement();
    latency_report();
    
    // Free the dynamically allocated memory for the data
    free((void*)data);
    return 0;
}


/**
 * @brief Sends data to the server asynchronously in a new thread.
 *
 * This function creates a duplicate of the data to ensure thread safety and
 * launches a new thread to send the data using `sendToServerThread`. The main
 * thread continues without waiting for the completion of the new thread.
 *
 * @param data A pointer to the data to be sent.
 */
void asyncSendToServer(const char* data) {
    // Duplicate the data to pass it safely to the thread
    char* dataCopy = _strdup(data);
    if (!dataCopy) {
        fprintf(stderr, "Failed to duplicate data for sendToServer thread.\n");
        return;
    }

    // Launch the `sendToServerThread` function in a new thread
    HANDLE thread = (HANDLE)_beginthreadex(NULL, 0, sendToServerThread, (void*)dataCopy, 0, NULL);

    // Close the thread handle immediately; no need to join
    CloseHandle(thread);
}
