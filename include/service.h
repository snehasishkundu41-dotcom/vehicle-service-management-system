#ifndef SERVICE_H
#define SERVICE_H

#define MAX_SERVICES 100
#define VEHICLE_NO_LEN 20
#define DATE_LEN 15
#define DESC_LEN 100

// Service status enum
typedef enum {
    PENDING,
    COMPLETED
} ServiceStatus;

// Service record structure
typedef struct {
    int serviceId;
    char vehicleNo[VEHICLE_NO_LEN];
    char serviceDate[DATE_LEN];
    char description[DESC_LEN];
    ServiceStatus status;
} ServiceRecord;

// Function declarations
void initServiceModule();

int addServiceRecord(const char *vehicleNo, const char *date, const char *description);
void viewAllServiceRecords();
void searchServiceByVehicle(const char *vehicleNo);
int updateServiceStatus(int serviceId, ServiceStatus status);
int deleteServiceRecord(int serviceId);

#endif
