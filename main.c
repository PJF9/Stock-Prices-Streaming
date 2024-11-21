#include "fetch_data_utils.h"
#include "latency_utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>
#include <time.h>


int main() {
    // Initialize a CURL session
    CURL* curl = curl_easy_init();
    if (!curl) {
        fprintf(stderr, "Failed to initialize CURL.\n");
        return 1;
    }

    // Define a static list of headers for HTTP requests
    static struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Connection: keep-alive");

    // Configure CURL options for secure and reusable connections
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L); // Enable following redirects.
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L); // Enable SSL certificate verification
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L); // Verify that the certificate’s Common Name (CN) or Subject Alternative Name (SAN) matches the host in the URL
    curl_easy_setopt(curl, CURLOPT_CAINFO, getenv("CURL_CERTS_PATH"));
    curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers); // Attach the custom headers to the CURL session

    // Start the main loop
    fetchSendWait(curl);

    // Clean up and release the CURL resources
    curl_easy_cleanup(curl);

    return 0;
}
