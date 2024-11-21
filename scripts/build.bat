@echo off

:: Remove the build directory if it exists
if exist build (
    echo Removing existing build directory...
    rmdir /s /q build
)

:: Create a new build directory
echo Creating build directory...
mkdir build

:: Navigate to the build directory
cd build

:: Run CMake to configure the project with MinGW Makefiles
echo Configuring the project with CMake...
cmake .. -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release
if errorlevel 1 (
    echo CMake configuration failed.
    cd ..
    exit /b 1
)

:: Build the project
echo Building the project...
cmake --build . --config Release
if errorlevel 1 (
    echo Build failed.
    cd ..
    exit /b 1
)

:: Return to the original directory
cd ..

echo Build and configuration completed successfully.
