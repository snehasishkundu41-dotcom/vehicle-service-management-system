# Vehicle Service Management System - Project Documentation

## 1. Project Overview
This is a comprehensive **Vehicle Service Management System** designed to manage vehicle records, service history, and user authentication. It features a robust backend logic written in C and a highly stylized Command Line Interface (CLI).

> **Credit Note:**
> *   **Core Logic & Architecture:** Manually hand-written by the Developer.
> *   **UI Styling & Beautification:** Enhanced using AI assistance to implement ANSI color codes and 3D ASCII art.

---

## 2. File Structure & Purpose

The project follows a **Modular Architecture**, separating code into logical units for better maintainability.

### **Folder: `src/` (Source Code)**
*   **`main.c`**: The entry point of the application. It handles the `welcome_screen`, the main loop, and switches between `adminMenu` and `userMenu`.
*   **`auth.c`**: Handles all user-related logic:
    *   `registerUser()`: Adds new users to `users.dat`.
    *   `loginUser()`: Verifies credentials against the database.
    *   `createDefaultAdminIfNeeded()`: Automatically creates a default Admin account if none exists.
        *   **Logic:** It tries to open `users.dat`. If the file doesn't exist (fresh install), it creates it and adds the default Admin (`ID: 1001`, `Pass: admin123`). If the file exists but has no admins, it appends one. This ensures the system is never "locked out".

*   **`vehicle.c`**: Manages vehicle data:
    *   `addVehicle()`: Inputs vehicle details (Owner, Model, Year) and saves to `vehicles.dat`.
    *   `viewVehicles()`: Reads and displays all vehicles.
    *   `searchVehicle()`: Finds a specific vehicle by its number plate.
    *   `updateVehicle()`: Modifies existing vehicle details (Owner, Phone, Model, etc.).
    *   `deleteVehicle()`: Removes a vehicle record from the database.
*   **`service.c`**: Manages service history records:
    *   `addService()`: creates a new service job (Status: Pending).
    *   `viewServices()`: lists all service jobs.
    *   `updateServiceStatus()`: Changes a job status from "Pending" to "Completed".
    *   `deleteService()`: Removes a service record using its ID.
*   **`ui.c`**: **(AI Enhanced)** usage of UI helper functions. Contains the logic for colors, centering text, and Windows ANSI support.

### **Folder: `include/` (Header Files)**
*   **`auth.h`, `vehicle.h`, `service.h`**: Contain structure definitions (`struct User`, `struct Vehicle`) and function prototypes.
*   **`ui.h`**: Contains definitions for colors (`COLOR_RED`, `COLOR_GREEN`) and UI function declarations.

### **Folder: `data/` (Database)**
*   **`users.dat`, `vehicles.dat`, `services.dat`**: The binary files where all data is persistently stored.

---

## 3. Code Flow (How it runs)

1.  **Initialization**:
    *   The program starts in `main()`.
    *   It immediately calls `createDefaultAdminIfNeeded()` to ensure at least one admin exists (ID: 1001).
    *   It prints the **3D ASCII Title** via `welcome_screen()`.

2.  **Main Loop**:
    *   The user sees the **Main Menu** (Login / Register / Exit).
    *   **Login**: The user enters ID and Password. The system checks `users.dat`.
        *   If **Admin**: Redirects to `adminMenu()` (Can manage Vehicles & Services).
        *   If **User**: Redirects to `userMenu()` (Can only Search & View History).

3.  **Data Handling**:
    *   When data is saved (e.g., `addVehicle`), it uses `fwrite()` to append the C structure directly to a binary file.
    *   When data is read, it uses `fread()` to load structs back into memory for display.

---

## 4. UI Beautification (AI Contribution)

The visual layer of this project was upgraded to provide a professional "Console App" feel without changing the original logic.

### **How it works:**
*   **ANSI Escape Codes**: The system uses special character sequences (e.g., `\033[1;32m` for Green) to instruct the terminal to change text color.
*   **Standardization**: Instead of using random `printf` statements, the code now uses a dedicated module:
    *   `print_header("TITLE")`: Automatically centers and colors the title.
    *   `print_error("Msg")`: Automatically prints the message in **Red**.
    *   `print_success("Msg")`: Automatically prints the message in **Green**.
*   **Windows Support**: Since standard Windows CMD doesn't always support these codes, a special function `enable_ansi_support()` was added to force modern console behavior.

---

## 5. Build Automation (`build.bat`)

To ensure a smooth "Plug and Play" experience for any evaluator, a custom **Batch Script** was created.

### **Purpose**
Compiling C programs with multiple source files requires a complex command (e.g., `gcc src/main.c src/auth.c ... -o "Vehicle Service Management System.exe"`). Typing this manually is error-prone. The `build.bat` file automates this.

### **How it works**
1.  **Checks Environment**: First, it checks if `gcc` is installed on the system.
2.  **Compiles All Sources**: It automatically finds all `.c` files in `src/` and header files in `include/`.
3.  **Links & Builds**: It merges them into a single executable named `Vehicle Service Management System.exe`.
4.  **Error Handling**: If compilation fails (e.g., a syntax error), it pauses and shows the error message instead of closing immediately.

**Usage:** Just double-click `build.bat`, and the project updates instantly.
