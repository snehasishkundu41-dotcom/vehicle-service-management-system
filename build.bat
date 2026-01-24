@echo off
echo Building Vehicle Service Management System...

REM Check if gcc is available
where gcc >nul 2>nul
if %errorlevel% neq 0 (
    echo Error: GCC not found! Please install MinGW or ensure gcc is in your PATH.
    pause
    exit /b 1
)

REM Compile the project
gcc -o "Vehicle Service Management System.exe" src/main.c src/auth.c src/vehicle.c src/service.c src/ui.c -I include

if %errorlevel% equ 0 (
    echo.
    echo ---------------------------------------
    echo Build Successful! [Vehicle Service Management System.exe]
    echo ---------------------------------------
    echo You can run the app using: ".\Vehicle Service Management System.exe"
) else (
    echo.
    echo ---------------------------------------
    echo Build Failed!
    echo ---------------------------------------
)

pause
