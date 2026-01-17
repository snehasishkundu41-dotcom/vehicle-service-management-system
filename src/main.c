#include <stdio.h>
#include <stdlib.h>

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
    printf("------------------------------");
    printf("Enter your choice: ");
    scanf("%d", &choice);
}

int main()
{
    welcome_screen();

    while (1)
    {
        int choice = main_menu();

        switch (choice)
        {
        case 1:
            printf("login feature coming soon....\n");
            break;
        case 2:
            printf("Register feature coming soon...\n");
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