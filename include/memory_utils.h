#ifndef MEM_H
#define MEM_H

#include <stdio.h>


/**
 * @brief Structure to manage a dynamically allocated memory buffer.
 *
 * This structure is used to store data received from CURL. The `data` field
 * is a pointer to the dynamically allocated memory block, and the `size` field
 * tracks the total size of the data stored in the buffer.
 */
typedef struct {
    char* data;
    size_t size;
} MemoryBuffer;



/**
 * @brief Callback function for writing CURL response data into a memory buffer.
 *
 * This function is used with CURL's `WRITEFUNCTION` option to handle incoming
 * data. It appends the data to the `MemoryBuffer` provided by the user, resizing
 * the memory dynamically as needed.
 *
 * @param contents Pointer to the data received from CURL.
 * @param size Size of each data element.
 * @param nmemb Number of elements in the data.
 * @param userp Pointer to a user-provided `MemoryBuffer` structure.
 * @return The total size of the data written to the buffer, or 0 if an error occurred.
 *
 * @note The `MemoryBuffer` must be initialized with `data = NULL` and `size = 0`
 *       before the first call to this function.
 */
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp);


#endif
