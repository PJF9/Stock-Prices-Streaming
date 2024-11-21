#ifndef FETCH_DATA_H
#define FETCH_DATA_H

#include <curl/curl.h>

#define API_KEY getenv("FINEHUB_API")
#define BASE_URL "https://finnhub.io/api/v1/quote"
#define SYMBOL "BINANCE:SOLUSDT"
#define INTERVAL_M 1


/**
 * @brief Periodically fetches data and sends it to a server.
 *
 * This function runs in an infinite loop. At each interval:
 * - It waits until the start of the next interval.
 * - It measures latency for the operation.
 * - It fetches stock data from the Finnhub API asynchronously.
 *
 * @param curl A pointer to an initialized CURL object.
 */
void fetchSendWait(CURL* curl);


#endif // FETCH_DATA_H
