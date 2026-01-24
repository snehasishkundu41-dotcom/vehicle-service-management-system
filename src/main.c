#include <stdio.h>
#include <stdlib.h>
#include "../include/auth.h"
#include "../include/vehicle.h"
#include "../include/service.h"

void welcome_screen()
{
    printf("=======================================\n");
    printf("   Vehicle Service Management Sytem\n");
    printf("=======================================\n");
}

int main_menu()
{
    int choice;

    printf("\n--------Main Menu----------\n");
    printf("1.Login\n");
    printf("2.Register(users)\n");
    printf("3.Exit\n");
    printf("------------------------------\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    return choice;
}



void adminMenu(){
    int choice;

    while(1){
        printf("\n==========ADMIN MENU===========\n");
        printf("1. Vehicle Management\n");
        printf("2. Service Records\n");
        printf("3. Logout\n");
        printf("==================================\n");
        printf("Enter choice: ");
        scanf("%d", &choice);


    switch(choice){
        case 1:
        vehicleMenu();
        break;

        case 2:
        serviceMenu();
        break;

        case 3:
        printf("\nLogging out...\n");
        return; // goes back to main menu

        default:
        printf("\nInvalid choice. Try again.\n");

    }
}
}

void userMenu(){
    int choice;
    while(1){
        printf("\n=============USER MENU==============\n");
        printf("1. View Service History\n");
        printf("2. Search Vehicle\n");
        printf("3.Logout\n");
        printf("======================================\n");
        printf("Enter choice: ");
        scanf("%d", &choice);


        switch(choice){
            case 1:
            searchServiceByVehicle();
            break;

            case 2:
            searchVehicle();
            break;


            case 3:
            printf("\nLogging out...\n");
            return;

            default:
            printf("\nInvalid choice. Try again.\n");
            
        }

     }



}
int main()
{
    welcome_screen();
    createDefaultAdminIfNeeded();

    while (1)
    {
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
            else{
                printf("\nLogin failed.Try again. \n");
            }

            break;

        }
        case 2:
            registerUser();
            break;
        case 3:
            printf("Exiting..Good Bye!\n");
            exit(0);

        default:
            printf("Invalid Choice,please try again\n");
        }
    }
    return 0;
}