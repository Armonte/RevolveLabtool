@echo off
setlocal EnableDelayedExpansion

:: Get the directory where the batch file is located
set "SCRIPT_DIR=%~dp0"
:: Remove trailing backslash
set "SCRIPT_DIR=%SCRIPT_DIR:~0,-1%"

:: Check if VS2022 is installed in the default location
set "VS2022_PATH=C:\Program Files\Microsoft Visual Studio\2022\Community"
if not exist "%VS2022_PATH%" (
    echo Visual Studio 2022 not found at default location.
    echo Please modify the script with your Visual Studio path.
    pause
    exit /b 1
)

:: Setup VS2022 x86 environment
call "%VS2022_PATH%\VC\Auxiliary\Build\vcvars32.bat"

:: Create and enter build directory
if not exist "%SCRIPT_DIR%\build" mkdir "%SCRIPT_DIR%\build"
cd /d "%SCRIPT_DIR%\build"

echo Current directory: %CD%
echo Source directory: %SCRIPT_DIR%

:: Configure and build
cmake -G "NMake Makefiles" -DCMAKE_BUILD_TYPE=Debug "%SCRIPT_DIR%"
if errorlevel 1 (
    echo CMake configuration failed
    cd /d "%SCRIPT_DIR%"
    pause
    exit /b 1
)

cmake --build .
if errorlevel 1 (
    echo Build failed
    cd /d "%SCRIPT_DIR%"
    pause
    exit /b 1
)

:: Return to original directory
cd /d "%SCRIPT_DIR%"

echo Build completed successfully!
pause