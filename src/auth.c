#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/auth.h"
#include "../include/ui.h"

#define USERS_FILE "data/users.dat"

void registerUser()
{
    User u;
    FILE *fp;
    print_header("REGISTER NEW USER");

    // take input
    print_input_prompt("Enter User ID: ");
    scanf("%d", &u.user_id);

    print_input_prompt("Enter Name: ");
    scanf(" %39[^\n]", u.name); // reads full line including spaces

    print_input_prompt("Enter Password: ");
    scanf(" %19s", u.password); // reads single word password

    // set role automatically as user
    u.role = ROLE_USER;

    // open file in append binary mode
    fp = fopen(USERS_FILE, "ab");

    if (fp == NULL)
    {
        print_error("Unable to open users file!");
        return;
    }

    // write structure to file
    fwrite(&u, sizeof(User), 1, fp);

    fclose(fp);

    print_success("User Registered Successfully");
}

// Now writing function for loginuser()

int loginUser()
{
    User u;
    FILE *fp;

    int id;
    char pass[20];

    print_subheader("LOGIN");
    
    print_input_prompt("Enter User ID: ");
    scanf("%d", &id);

    print_input_prompt("Enter password: ");
    scanf(" %19s", pass);

    // open users file in read binary mode
    fp = fopen(USERS_FILE, "rb");

    if (fp == NULL)
    {
        print_error("Users file not found!");
        return 0;
    }

    // read users records one by one
    while (fread(&u, sizeof(User), 1, fp))
    {
        if (u.user_id == id && strcmp(u.password, pass) == 0)
        {
            fclose(fp);
            char welcome_msg[100];
            sprintf(welcome_msg, "Login Successful! Welcome %s", u.name);
            print_success(welcome_msg);
            // wait_for_enter(); // Optional: pause to let user see success
            return u.role; // ROLE_ADMIN or ROLE_USER
        }
    }

    fclose(fp);
    print_error("Login Failed! Wrong User ID or Password.");

    return 0;
}
// Code for creating default admin if needed

void createDefaultAdminIfNeeded()
{
    FILE *fp;
    User u;
    int adminFound = 0;

    // Try opening file in read mode to check if it exist or not
    fp = fopen(USERS_FILE, "rb");

    // If file doesn't exist, create it and add default main
    if (fp == NULL)
    {
        fp = fopen(USERS_FILE, "wb");
        if (fp == NULL)
        {
            print_error("Cannot create users file!");
            return;
        }

        // Default admin details

        u.user_id = 1001;
        strcpy(u.name, "Admin");
        strcpy(u.password, "admin123");
        u.role = ROLE_ADMIN;

        fwrite(&u, sizeof(User), 1, fp);
        fclose(fp);

        print_info("Default Admin Created: ID=1001, PASS=admin123");
        return;
    }

    // file exist: check if any admin already exist

    while (fread(&u, sizeof(User), 1, fp))
    {
        if (u.role == ROLE_ADMIN)
        {
            adminFound = 1;
            break;
        }
    }
    fclose(fp);

    // if admin not found, add admin by appending
    if (adminFound == 0)
    {
        fp = fopen(USERS_FILE, "ab");
        if (fp == NULL)
        {
            print_error("Cannot open users file!");
            return;
        }

        // Default admin details

        u.user_id = 1001;
        strcpy(u.name, "Admin");
        strcpy(u.password, "admin123");
        u.role = ROLE_ADMIN;

        fwrite(&u, sizeof(User), 1, fp);
        fclose(fp);

        print_info("Default Admin Created: ID=1001, PASS=admin123");
    }
}
