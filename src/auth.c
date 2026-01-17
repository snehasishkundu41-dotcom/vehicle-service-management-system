#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "../include/auth.h"

#define USERS_FILE "../data/users.dat"

void registerUser(){
    User u;
    FILE *fp;
    printf("\n-------Register(User/Staff)------\n");

    // take input
    printf("Enter User ID: ");
    scanf("%d", &u.user_id);

    printf("Enter Name: ");
}