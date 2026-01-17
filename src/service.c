#include <stdio.h>
#include <string.h>
#include "service.h"

static ServiceRecord services[MAX_SERVICES];
static int serviceCount = 0;
static int nextServiceId = 1;

// Initialize service module
void initServiceModule() {
    serviceCount = 0;
    nextServiceId = 1;
}

// Add a new service record
int addServiceRecord(const char *vehicleNo, const char *date, const char *description) {
    if (serviceCount >= MAX_SERVICES) {
        return -1;
    }

    ServiceRecord *s = &services[serviceCount];
    s->serviceId = nextServiceId++;
    strcpy(s->vehicleNo, vehicleNo);
    strcpy(s->serviceDate, date);
    strcpy(s->description, description);
    s->status = PENDING;

    serviceCount++;
    return s->serviceId;
}

// View all service records
void viewAllServiceRecords() {
    if (serviceCount == 0) {
        printf("No service records found.\n");
        return;
    }

    for (int i = 0; i < serviceCount; i++) {
        printf("ID: %d | Vehicle: %s | Date: %s | Status: %s | Desc: %s\n",
               services[i].serviceId,
               services[i].vehicleNo,
               services[i].serviceDate,
               services[i].status == PENDING ? "Pending" : "Completed",
               services[i].description);
    }
}

// Search service by vehicle number
void searchServiceByVehicle(const char *vehicleNo) {
    int found = 0;

    for (int i = 0; i < serviceCount; i++) {
        if (strcmp(services[i].vehicleNo, vehicleNo) == 0) {
            printf("ID: %d | Date: %s | Status: %s | Desc: %s\n",
                   services[i].serviceId,
                   services[i].serviceDate,
                   services[i].status == PENDING ? "Pending" : "Completed",
                   services[i].description);
            found = 1;
        }
    }

    if (!found) {
        printf("No service record found for vehicle %s\n", vehicleNo);
    }
}

// Update service status
int updateServiceStatus(int serviceId, ServiceStatus status) {
    for (int i = 0; i < serviceCount; i++) {
        if (services[i].serviceId == serviceId) {
            services[i].status = status;
            return 1;
        }
    }
    return 0;
}

// Delete service record
int deleteServiceRecord(int serviceId) {
    for (int i = 0; i < serviceCount; i++) {
        if (services[i].serviceId == serviceId) {
            for (int j = i; j < serviceCount - 1; j++) {
                services[j] = services[j + 1];
            }
            serviceCount--;
            return 1;
        }
    }
    return 0;
}
