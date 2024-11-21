@echo off

:: Set project directory (optional)
set PROJECT_DIR=%CD%

:: Remove the build directory if it exists
if exist "%PROJECT_DIR%\build" (
    echo Removing existing build directory...
    rmdir /s /q "%PROJECT_DIR%\build"
)

:: Create a new build directory
echo Creating build directory...
mkdir "%PROJECT_DIR%\build"

:: Navigate to the build directory
cd "%PROJECT_DIR%\build"

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

:: Clear the screen for clarity
cls

:: Run the executable (make sure to change this to your executable name)
echo Running the executable...
"%PROJECT_DIR%\build\main.exe"
if errorlevel 1 (
    echo Execution failed.
    exit /b 1
)

echo Execution completed successfully.
