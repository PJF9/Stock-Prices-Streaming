#include "memory_utils.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


/**
 * @brief Callback function for writing CURL response data into a memory buffer.
 *
 * This function is used as the `WRITEFUNCTION` callback for CURL to handle
 * incoming data. It appends the data to a dynamically allocated memory buffer,
 * resizing the buffer as necessary. If memory allocation fails, an error is
 * logged, and the operation is terminated.
 *
 * @param contents A pointer to the data received from CURL.
 * @param size The size of each data element.
 * @param nmemb The number of elements in the data.
 * @param userp A pointer to the user-provided memory buffer (`MemoryBuffer`).
 * @return The total size of the data written to the buffer, or 0 if an error occurred.
 *
 * @note The user-provided `MemoryBuffer` structure must be initialized with
 *       `data = NULL` and `size = 0` before the first call to this function.
 */
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
     // Calculate the total size of the incoming data
    size_t totalSize = size * nmemb;

    // Cast the user pointer to a MemoryBuffer structure
    MemoryBuffer* mem = (MemoryBuffer*)userp;

    // Reallocate memory to fit the new data
    char* ptr = realloc(mem->data, mem->size + totalSize + 1);
    if (ptr == NULL) {
        fprintf(stderr, "Out of memory!\n");
        return 0;
    }

    mem->data = ptr; // Update the memory buffer pointer
    memcpy(&(mem->data[mem->size]), contents, totalSize); // Append the new data
    mem->size += totalSize; // Update the size of the memory buffer
    mem->data[mem->size] = '\0';

    return totalSize;
}
