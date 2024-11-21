#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H


/**
 * @brief Sends data to the server asynchronously in a new thread.
 *
 * This function duplicates the input data to ensure thread safety and
 * launches a new thread to send the data using a thread-safe wrapper.
 *
 * @param data A pointer to the data to be sent.
 *
 * @note The input `data` must be a valid null-terminated string. The function
 *       internally duplicates the string to avoid issues in multithreaded scenarios.
 */
void asyncSendToServer(const char* data);


#endif // SERVER_UTILS_H
