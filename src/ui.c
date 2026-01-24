#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#endif
#include "../include/ui.h"

// Helper to enable ANSI support on Windows 10+
void enable_ansi_support() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

void print_centered(const char* text) {
    int len = strlen(text);
    int padding = (TERMINAL_WIDTH - len) / 2;
    if (padding < 0) padding = 0;
    
    for (int i = 0; i < padding; i++) {
        putchar(' ');
    }
    printf("%s\n", text);
}

void print_centered_colored(const char* text, const char* color) {
    int len = strlen(text);
    int padding = (TERMINAL_WIDTH - len) / 2;
    if (padding < 0) padding = 0;
    
    for (int i = 0; i < padding; i++) {
        putchar(' ');
    }
    printf("%s%s%s\n", color, text, COLOR_RESET);
}

void print_ascii_title() {
    printf(COLOR_CYAN);
    printf(" __      __   _     _      _        \n");
    printf(" \\ \\    / /  | |   (_)    | |       \n");
    printf("  \\ \\  / /___| |__  _  ___| | ___   \n");
    printf("   \\ \\/ // _ \\ '_ \\| |/ __| |/ _ \\  \n");
    printf("    \\  /|  __/ | | | | (__| |  __/  \n");
    printf("     \\/  \\___|_| |_|_|\\___|_|\\___|  \n");
    printf(COLOR_RESET);
    
    printf(COLOR_MAGENTA);
    printf("   ___                  _              \n");
    printf("  / __| ___ _ ___  _(_)__ ___      \n");
    printf("  \\__ \\/ -_) '_\\ V / / _/ -_)     \n");
    printf("  |___/\\___|_|  \\_/|_\\__\\___|     \n");
    printf(COLOR_RESET);
    
    printf(COLOR_BLUE);
    printf("   __  __                                   _    \n");
    printf("  |  \\/  |__ _ _ _  __ _ __ _ ___ _ __  ___| |_  \n");
    printf("  | |\\/| / _` | ' \\/ _` / _` / -_) '  \\/ -_)  _| \n");
    printf("  |_|  |_\\__,_|_||_\\__,_\\__, \\___|_|_|_\\___|\\__| \n");
    printf("                        |___/                    \n");
    printf(COLOR_RESET);
    printf("\n");
}

void print_divider() {
    printf(COLOR_CYAN);
    for (int i = 0; i < TERMINAL_WIDTH; i++) {
        putchar('=');
    }
    printf(COLOR_RESET "\n");
}

void print_header(const char* title) {
    // Ensure ANSI is enabled if on Windows (call this once typically, but safe here)
    enable_ansi_support(); // Ideally call this once in main, but keeping it robust for now
    
    clear_screen();
    print_divider();
    printf("\n");
    print_centered_colored(title, COLOR_BOLD COLOR_MAGENTA);
    printf("\n");
    print_divider();
    printf("\n");
}

void print_subheader(const char* title) {
    printf("\n");
    print_centered_colored(title, COLOR_YELLOW);
    printf(COLOR_CYAN);
    int len = strlen(title);
    int padding = (TERMINAL_WIDTH - len) / 2;
    if (padding < 0) padding = 0;
     for (int i = 0; i < padding; i++) {
        putchar(' ');
    }
    for(int i=0; i<len; i++) putchar('-');
    printf(COLOR_RESET "\n\n");
}

void print_menu_item(int index, const char* text) {
    // Center the menu items roughly if desired, or just indent them nicely
    // Let's try a centered-ish approach or a nice indented list
    // Simple indent looks professional for menus
    // printf("        %s[%d]%s %s\n", COLOR_CYAN, index, COLOR_RESET, text);
    
    // Let's center the menu block itself effectively by calculating a left margin
    // Assuming a menu width of ~40 chars
    int margin = (TERMINAL_WIDTH - 40) / 2;
    for(int i=0; i<margin; i++) putchar(' ');
    
    printf("%s[%d]%s  %s\n", COLOR_CYAN, index, COLOR_RESET, text);
}

void print_error(const char* message) {
    printf("\n%s[!] ERROR: %s%s\n", COLOR_RED, message, COLOR_RESET);
}

void print_success(const char* message) {
    printf("\n%s[*] SUCCESS: %s%s\n", COLOR_GREEN, message, COLOR_RESET);
}

void print_info(const char* message) {
    printf("\n%s[i] INFO: %s%s\n", COLOR_BLUE, message, COLOR_RESET);
}

void print_input_prompt(const char* prompt) {
    printf("\n%s>> %s%s", COLOR_YELLOW, prompt, COLOR_RESET);
}

void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void wait_for_enter() {
    printf("\n%sPress [ENTER] to continue...%s", COLOR_BOLD, COLOR_RESET);
    while(getchar() != '\n'); 
    getchar(); // Catch the actual enter key
}
