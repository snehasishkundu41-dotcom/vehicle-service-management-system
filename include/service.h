#ifndef SERVICE_H
#define SERVICE_H

// lengths
#define VEHICLE_NO_LEN 20
#define SERVICE_DESC_LEN 50
#define SERVICE_STATUS_LEN 15

// Service structure
typedef struct {
    int serviceId;
    char vehicleNo[VEHICLE_NO_LEN];
    char description[SERVICE_DESC_LEN];
    int cost;
    char status[SERVICE_STATUS_LEN];
} Service;

// Service management menu
void serviceMenu();

// CRUD operations
void addService();
void viewServices();
void searchServiceByVehicle();
void updateServiceStatus();

#endif
