#include <stdio.h>
#include <stdlib.h>
#include "../include/auth.h"
#include "../include/vehicle.h"
#include "../include/service.h"
#include "../include/ui.h"

void welcome_screen()
{
    print_ascii_title();
    print_centered("Welcome to the most advanced service manager");
    printf("\n");
    print_divider();
}

int main_menu()
{
    int choice;

    print_subheader("MAIN MENU");
    
    print_menu_item(1, "Login");
    print_menu_item(2, "Register (New User)");
    print_menu_item(3, "Exit");
    
    printf("\n");
    print_input_prompt("Enter your selection: ");
    scanf("%d", &choice);

    return choice;
}

void adminMenu(){
    int choice;

    while(1){
        print_header("ADMIN DASHBOARD");
        
        print_menu_item(1, "Vehicle Management");
        print_menu_item(2, "Service Records");
        print_menu_item(3, "Logout");
        
        printf("\n");
        print_input_prompt("Enter choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
            vehicleMenu();
            break;

            case 2:
            serviceMenu();
            break;

            case 3:
            print_info("Logging out...");
            return; // goes back to main menu

            default:
            print_error("Invalid choice. Try again.");
        }
    }
}

void userMenu(){
    int choice;
    while(1){
        print_header("USER DASHBOARD");
        
        print_menu_item(1, "View Service History");
        print_menu_item(2, "Search Vehicle");
        print_menu_item(3, "Logout");
        
        printf("\n");
        print_input_prompt("Enter choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
            searchServiceByVehicle();
            break;

            case 2:
            searchVehicle();
            break;

            case 3:
            print_info("Logging out...");
            return;

            default:
            print_error("Invalid choice. Try again.");
        }
     }
}

int main()
{
    // Enable ANSI support on Windows at start
    #ifdef _WIN32
    system("cls"); // Quick clear to reset
    #endif
    
    while (1)
    {
        welcome_screen();
        createDefaultAdminIfNeeded();
        
        int choice = main_menu();

        switch (choice)
        {
        case 1:{
            int role = loginUser();

            if(role ==  ROLE_ADMIN){
                adminMenu();
            }
            else if(role == ROLE_USER){
                userMenu();
            }
            // Error handled in loginUser
            break;

        }
        case 2:
            registerUser();
            break;
        case 3:
            print_info("Exiting... Good Bye!");
            exit(0);

        default:
            print_error("Invalid Choice, please try again");
        }
    }
    return 0;
}