cmake_minimum_required(VERSION 3.10)

# Project name and version
project(STOCK_PRICE_STREAMING VERSION 1.0 LANGUAGES C)

# Set the C standard
set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED ON)

# Set executable name
set(EXECUTABLE_NAME main)

# Specify the directories containing the include files
include_directories(include)

# Define the source files
set(SOURCES
    src/fetch_data_utils.c
    src/json_utils.c
    src/latency_utils.c
    src/memory_utils.c
    src/server_utils.c
    main.c
)

# Set cURL root directory
set(CURL_ROOT $ENV{C_LIBRARIES_PATH}/curl-8.11.0_1-win32-mingw)
include_directories(${CURL_ROOT}/include)
link_directories(${CURL_ROOT}/lib)

# Set jansson root directory
set(JANSSON_ROOT $ENV{C_LIBRARIES_PATH}/jansson/build)
include_directories(${JANSSON_ROOT}/include)
link_directories(${JANSSON_ROOT}/lib)

# Add the executable
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Link cURL and its dependencies
target_link_libraries(${EXECUTABLE_NAME} PRIVATE curl ws2_32 wldap32)

# Link with jansson library
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ${JANSSON_ROOT}/lib/libjansson.a)

# Link with Winsock library
target_link_libraries(${EXECUTABLE_NAME} PRIVATE ws2_32)

# Copy DLL to the output directory after build
add_custom_command(
    TARGET ${EXECUTABLE_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
            "${CURL_ROOT}/bin/libcurl.dll"
            $<TARGET_FILE_DIR:${EXECUTABLE_NAME}>
)

# Debugging information
message(STATUS "CURL include directory: ${CURL_ROOT}/include")
message(STATUS "CURL library directory: ${CURL_ROOT}/lib")
message(STATUS "JANSSON include directory: ${JANSSON_ROOT}/include")
message(STATUS "JANSSON library directory: ${JANSSON_ROOT}/lib")
