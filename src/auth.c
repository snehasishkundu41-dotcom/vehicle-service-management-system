#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/auth.h"

#define USERS_FILE "data/users.dat"

void registerUser()
{
    User u;
    FILE *fp;
    printf("\n-------Register(User/Staff)------\n");

    // take input
    printf("Enter User ID: ");
    scanf("%d", &u.user_id);

    printf("Enter Name: ");
    scanf(" %39[^\n]", u.name); // reads full line including spaces

    printf("Enter Password: ");
    scanf(" %19s", u.password); // reads single word password

    // set role automatically as user
    u.role = ROLE_USER;

    // open file in append binary mode
    fp = fopen(USERS_FILE, "ab");

    if (fp == NULL)
    {
        printf("Error: Unable to open users file!\n");
        return;
    }

    // write structure to file
    fwrite(&u, sizeof(User), 1, fp);

    fclose(fp);

    printf("\n user Registered Successfully\n");
}

// Now writing function for loginuser()

int loginUser()
{
    User u;
    FILE *fp;

    int id;
    char pass[20];

    printf("\n------------Login-------------\n");
    printf("Enter User ID: ");
    scanf("%d", &id);

    printf("Enter password: ");
    scanf(" %19s", pass);

    // open users file in read binary mode
    fp = fopen(USERS_FILE, "rb");

    if (fp == NULL)
    {
        printf("Error: users file not found!\n");
        return 0;
    }

    // read users records one by one
    while (fread(&u, sizeof(User), 1, fp))
    {
        if (u.user_id == id && strcmp(u.password, pass) == 0)
        {
            fclose(fp);
            printf("\nLogin Successful! Welcome %s\n", u.name);
            return u.role; // ROLE_ADMIN or ROLE_USER
        }
    }

    fclose(fp);
    printf("\nLogin Failed! Wrong User ID or Password.\n");

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
            printf("Error: Cannot create users file!\n");
            return;
        }

        // Default admin details

        u.user_id = 1001;
        strcpy(u.name, "Admin");
        strcpy(u.password, "admin123");
        u.role = ROLE_ADMIN;

        fwrite(&u, sizeof(User), 1, fp);
        fclose(fp);

        printf("\n[Default Admin Created: ID=1001, PASS=admin123]\n");
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
            printf("Error: Cannot open users file!\n");
            return;
        }

        // Default admin details

        u.user_id = 1001;
        strcpy(u.name, "Admin");
        strcpy(u.password, "admin123");
        u.role = ROLE_ADMIN;

        fwrite(&u, sizeof(User), 1, fp);
        fclose(fp);

        printf("\n[Default Admin Created: ID=1001, PASS=admin123]\n");
    }
}
