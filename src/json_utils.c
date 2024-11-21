#include "json_utils.h"
#include <jansson.h>
#include <stdio.h>


/**
 * @brief Extracts a numeric value associated with a given key from a JSON string.
 *
 * This function uses the Jansson library to parse a JSON string, retrieve the value
 * associated with the specified key, and return it as a formatted string. If the key
 * does not exist, or the value is not a number, a default "N/A" is returned.
 *
 * @param json A pointer to the JSON string to parse.
 * @param key The key whose associated value is to be extracted.
 * @return A pointer to a static buffer containing the extracted value as a string,
 *         or "N/A" if the key is not found or the value is not numeric.
 * 
 * @note The returned string is stored in a static buffer, so the content will be 
 *       overwritten on subsequent calls.
 * @note This function assumes the JSON input is well-formed; malformed JSON will 
 *       cause an error message to be printed.
 */
const char* extractValueUsingJansson(const char* json, const char* key) {
    static char value[BUFFER_SIZE]; // Buffer to store the value
    json_error_t error;

    // Parse the JSON string into a JSON object
    json_t* root = json_loads(json, 0, &error);
    if (!root) {
        fprintf(stderr, "JSON parsing error: %s\n", error.text);
        return "N/A";
    }

    // Retrieve the value associated with the key
    json_t* jsonValue = json_object_get(root, key);
    if (!jsonValue || !json_is_number(jsonValue)) {
        fprintf(stderr, "Key not found or not a number: %s\n", key);
        json_decref(root); // Free JSON object memory
        return "N/A";
    }

    // Convert the JSON number to a string
    snprintf(value, sizeof(value), "%.2f", json_number_value(jsonValue));

    json_decref(root); // Free JSON object memory
    return value;
}
