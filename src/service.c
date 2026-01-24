#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../include/service.h"

#define SERVICE_FILE "data/services.dat"


// Writing function for add service
void addService(){
    Service s;
    FILE *fp;
    printf("\n-------------------Add Service----------------------\n");

    // taking input

    printf("Enter Service ID: ");
    scanf("%d",&s.serviceId);
    printf("Enter vehicle NO: ");
    scanf(" %19s",s.vehicleNo);
    printf("Enter Service Description: ");
    scanf(" %39[^\n]",s.description);
    printf("Enter Service Cost: ");
    scanf("%d",&s.cost);
    strcpy(s.status,"Pending");

    fp = fopen(SERVICE_FILE,"ab");
    if(fp == NULL){
        printf("Unable to open service file");
        return;
    }
    
    // writing the service details in service.dat file

    fwrite(&s,sizeof(Service),1,fp);
    fclose(fp);

    printf("Service record added successfuly!\n");
}
// Now writing function to view services 
void viewServices(){
    Service s;
    FILE *fp;

    fp = fopen(SERVICE_FILE,"rb");

    if(fp == NULL){
        printf("Error:No Service Records found\n");
        return;
    }

    while(fread(&s,sizeof(Service),1,fp)){
        printf("\n==================================\n");
        printf("Service ID: %d\n",s.serviceId);
        printf("Vehicle No: %s\n",s.vehicleNo);
        printf("Description: %s\n",s.description);
        printf("Cost: %d\n",s.cost);
        printf("Status: %s\n",s.status);
        printf("====================================\n");
    }

    fclose(fp);


}

// Now writing the function to search vehicle by number

void searchServiceByVehicle(){
    Service s;
    FILE *fp;
    int found = 0;
    char searchedNo[VEHICLE_NO_LEN];

    printf("Enter Vehicle No: ");
    scanf(" %19s",searchedNo);

    fp = fopen(SERVICE_FILE,"rb");

    if(fp == NULL){
        printf("No service records exist");
        return;
    }

    while(fread(&s,sizeof(Service),1,fp)){
        if(strcmp(searchedNo,s.vehicleNo)==0){
            found = 1;
        printf("\n==================================\n");
        printf("Service ID: %d\n",s.serviceId);
        printf("Description: %s\n",s.description);
        printf("Cost: %d\n",s.cost);
        printf("Status: %s\n",s.status);
        printf("====================================\n");

        }
    }

    if(found == 0){
        printf("No service record is found with your given number\n");
    }

    fclose(fp);
}

// writing function to update service status

void updateServiceStatus(){
    Service s;
    FILE *fp;
    int serviceIDToUpdate;
    int found = 0;

    printf("Enter Service ID to update status: ");
    scanf("%d",&serviceIDToUpdate);

    fp = fopen(SERVICE_FILE,"rb+");

    if(fp == NULL){
        printf("No service records found\n");
        return;
    }

    while(fread(&s,sizeof(Service),1,fp)){
        if(serviceIDToUpdate == s.serviceId){
            found = 1;
            strcpy(s.status,"Completed");
            fseek(fp,-sizeof(Service), SEEK_CUR);

            fwrite(&s,sizeof(Service),1,fp);
            break;
        }
    }
    if(found){
        printf("Service Status updated successfully!\n");
    }
    else{
        printf("Service ID not found\n");
    }

    fclose(fp);
}



// Now writing service management menu

void serviceMenu(){

    int choice;

    while(1){
        printf("\n----------------Service Management Menu-----------------\n");
        printf("1.Add Service Record\n");
        printf("2.View Service Records\n");
        printf("3.Search Service by Vehicle No\n");
        printf("4.Update Service Status\n");
        printf("5.Return to Main Menu\n");

        printf("------------------------------------------------------------\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1:
            addService();
            break;

            case 2:
            viewServices();
            break;

            case 3:
            searchServiceByVehicle();
            break;

            case 4:
            updateServiceStatus();
            break;

            case 5:
            return; // goes back to main menu

            default:
            printf("Invalid choice. Try again.\n");
        }
    }


}