#ifndef AUTH_H
#define AUTH_h

#define ROLE_ADMIN 1
#define ROLE_USER 2

typedef struct{
    int user_id;
    char name[40];
    char password[20];
    int role;
}User;

void registerUser();
int loginUser();
void createDefaultAdminIfNeeded();

#endif