#ifndef VEHICLE_H
#define VEHICLE_H

#define VEHICLE_NO_LEN 20
#define OWNER_NAME_LEN 40
#define MODEL_LEN 30
#define PHONE_LEN 15

typedef struct{
    char vehicleNo[VEHICLE_NO_LEN];
    char ownerName[OWNER_NAME_LEN];
    char phone[PHONE_LEN];
    char model[MODEL_LEN];
    char type[10];
    int year;


}Vehicle;

// Vehicle module main menu

void vehicleMenu();

// CRUD operations

void addVehicle();
void viewVehicles();
void searchVehicle();

#endif