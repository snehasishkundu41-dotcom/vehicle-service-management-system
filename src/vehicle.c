#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../include/vehicle.h"

#define VEHICLE_FILE "data/vehicles.dat"


void addVehicle(){

    Vehicle v;
    FILE *fp;

    printf("\n----------Add Vehicles----------\n");

    // take input
    printf("Enter vehicle NO: ");
    scanf(" %19s",v.vehicleNo);

    printf("Enter Name of the Owner: ");
    scanf(" %39[^\n]",v.ownerName);

    printf("Enter phone number: ");
    scanf(" %14s",v.phone);

    printf("Enter model of your vehicle: ");
    scanf(" %29[^\n]",v.model);

    printf("Enter type of your vehicle: ");
    scanf(" %9s", v.type);

    printf("Enter Year:");
    scanf("%d",&v.year);


    fp = fopen(VEHICLE_FILE,"ab");
    if(fp == NULL){
        printf("Error:Unable to open vehicles  file\n ");
        return;
    }
    // write the details of vehicles in the file
    fwrite(&v,sizeof(Vehicle),1,fp);
    fclose(fp);

    printf("\n Vehicle added successfully");

}

    // Now for viewing vehicles
    void viewVehicles(){
        Vehicle v;
        FILE *fp;

        fp = fopen(VEHICLE_FILE,"rb");

        if(fp == NULL){
            printf("Error:No vehicles found\n");
            return;
        }

        while(fread(&v,sizeof(Vehicle),1,fp)){
            printf("Vehicle No: %s\n", v.vehicleNo);
            printf("Name of the owner: %s\n",v.ownerName);
            printf("Phone Number: %s\n",v.phone);
            printf("Vehicle Model: %s\n",v.model);
            printf("Vehicle Type: %s\n",v.type);
            printf("Year: %d\n",v.year);
        }

        fclose(fp);
    
    }
