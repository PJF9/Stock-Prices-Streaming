@echo off

:: Set project directory (optional)
set PROJECT_DIR=%CD%

:: Run the executable (make sure to change this to your executable name)
echo Running the executable...
"%PROJECT_DIR%\build\main.exe"
if errorlevel 1 (
    echo Execution failed.
    exit /b 1
)

echo Execution completed successfully.
