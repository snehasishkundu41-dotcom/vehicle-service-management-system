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
            printf("\n==================================\n");
            printf("Vehicle No: %s\n", v.vehicleNo);
            printf("Name of the owner: %s\n",v.ownerName);
            printf("Phone Number: %s\n",v.phone);
            printf("Vehicle Model: %s\n",v.model);
            printf("Vehicle Type: %s\n",v.type);
            printf("Year: %d\n",v.year);
            printf("====================================\n");
        }

        fclose(fp);
    }
        // Now for searching vehicles
        
    void searchVehicle(){
        Vehicle v;
        int found = 0;
        char searchedNo[VEHICLE_NO_LEN];
        FILE *fp;
        printf("--------------Search Vehicles--------------\n");
        printf("Enter Vehicle No: \n");
        scanf(" %19s",searchedNo);

        
        fp = fopen(VEHICLE_FILE,"rb");


        if(fp == NULL){
            printf("No vehicle records exist");
            return;
        }
        while(fread(&v,sizeof(Vehicle),1,fp)){
            if(strcmp(searchedNo,v.vehicleNo)==0){
                found = 1;
                printf("Name of the owner: %s\n",v.ownerName);
                printf("Phone Number: %s\n",v.phone);
                printf("Vehicle Model: %s\n",v.model);
                printf("Vehicle Type: %s\n",v.type);
                printf("Year: %d\n",v.year);

                break;
        }
         
    
     }

                if(found == 0){
                printf("Error: Vehicle not found\n");
                }

                fclose(fp);
 }


//  Now we gonna write the function for vehicle management menu


    void vehicleMenu(){
        int choice;
        

        while(1){


            printf("\n----------------Vehicle Management Menu-----------------\n");

            printf("1.Add Vehicles\n");
            printf("2.View Vehicles\n");
            printf("3.Search Vehicles\n");
            printf("4.Return to Main Menu\n");

            printf("------------------------------------------------------------\n");
            printf("Enter your choice: ");
            scanf("%d",&choice);


            switch(choice){
                case 1:
                addVehicle();
                break;
                
                case 2:
                viewVehicles();
                break;

                case 3:
                searchVehicle();
                break;

                case 4:
                return;

                default:
                printf("\nInvalid Choice.Choose again!\n");
                break;

            }

        }
    }


    
    
