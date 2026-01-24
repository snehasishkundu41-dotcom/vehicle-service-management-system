#ifndef UI_H
#define UI_H

// Color Definitions
#define COLOR_RESET   "\033[0m"
#define COLOR_RED     "\033[1;31m"
#define COLOR_GREEN   "\033[1;32m"
#define COLOR_YELLOW  "\033[1;33m"
#define COLOR_BLUE    "\033[1;34m"
#define COLOR_MAGENTA "\033[1;35m"
#define COLOR_CYAN    "\033[1;36m"
#define COLOR_WHITE   "\033[1;37m"
#define COLOR_BOLD    "\033[1m"

// UI Constants
#define TERMINAL_WIDTH 80

// Function Prototypes
void print_centered(const char* text);
void print_centered_colored(const char* text, const char* color);
void print_header(const char* title);
void print_subheader(const char* title);
void print_menu_item(int index, const char* text);
void print_error(const char* message);
void print_success(const char* message);
void print_info(const char* message);
void print_input_prompt(const char* prompt);
void print_ascii_title();
void print_divider();
void clear_screen();
void wait_for_enter();

#endif // UI_H
