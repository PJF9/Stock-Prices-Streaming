#ifndef JSON_UTILS_H
#define JSON_UTILS_H


/**
 * @def BUFFER_SIZE
 * @brief The size of the static buffer used for storing extracted JSON values.
 *
 * This constant defines the maximum length of the string representation
 * of a value extracted from a JSON object.
 */
#define BUFFER_SIZE 1024


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
const char* extractValueUsingJansson(const char* json, const char* key);


#endif // JSON_UTILS_H
