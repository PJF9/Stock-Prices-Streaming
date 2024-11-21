# Stock Price Fetcher and Server Communication

This project consists of a C-based client application that fetches stock prices from an API and sends the data to a Python server for processing or storage. It demonstrates seamless integration between C and Python through inter-process communication.

---

## Project Structure
```
build/                  # Directory for compiled binary files
include/                # Header files for the C client
    fetch_data_utils.h  
    json_utils.h        
    latency_utils.h     
    memory_utils.h      
    server_utils.h      
scripts/                # Utility scripts for building and running the project
    build_and_run.bat   
    build.bat           
    run.bat             
src/                    # Source files for the C client
    fetch_data_utils.c  
    json_utils.c        
    latency_utils.c     
    memory_utils.c      
    server_utils.c      
CMakeLists.txt          # Configuration file for building the C project
main.c                  # Entry point for the C client
python_server.py        # Python server for receiving stock price data
```
---

## Prerequisites

Before building and running this project, ensure you have the following installed on your system (this project has been created for Windows machines):
1. `C Compiler`: Use MinGW, which can be downloaded from [here](https://sourceforge.net/projects/mingw/).
2. `CMake`: Download it from [here](https://cmake.org/download/). Ensure that CMake and the compiler have the same architecture (e.g., x32).
3. `libcurl`: Download the compressed file from [here](https://curl.se/windows/).  Extract the files into a new folder, and create another folder to house all external packages. Update the naming in the *CMakeLists.txt* file to match your extracted folder (currently set to *curl-8.11.0_1-win32-mingw*).
4. `jansson`:  Clone the Jansson library from [here](https://github.com/akheron/jansson) to the same location as `libcurl`. Follow the build instructions provided on their official GitHub page. Then, create an environment variable named *C_LIBRARIES_PATH* pointing to the paths of both `curl` and `jansson` on your system.
5. `Curl Certificates`: Download the required certificates from the official Curl page [here](https://curl.se/docs/caextract.html). Create an environment variable named *CURL_CERTS_PATH* and set it to the location of these certificates.
6. `Finnhub API`: Visit [this page](https://finnhub.io/) to obtain a free API key from Finnhub. Create an environment variable named *FINNHUB_API* and set it to your API key.
7. `requirements.txt`: Install the necessary Python packages for the project:
```bash
pip install -r requirements.txt
```
And you're done!

---


## Setup Instructions

1.  `Build the Client`: Run the build script:
```bash
script/build.bat
```

2. `Run the Server`: Run the Python server:
```bash
python python_server.py
```

3. `Run the Client`: Ensure the Python server is running. Execute the run script:
```bash
scripts/run.bat
```

To build and run both the client and server:
```bash
scripts/build_and_run.bat
```
