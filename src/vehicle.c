#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../include/vehicle.h"
#include "../include/ui.h"

#define VEHICLE_FILE "data/vehicles.dat"


void addVehicle(){

    Vehicle v;
    FILE *fp;

    print_header("ADD NEW VEHICLE");

    // take input
    print_input_prompt("Enter vehicle NO: ");
    scanf(" %19s",v.vehicleNo);

    print_input_prompt("Enter Name of the Owner: ");
    scanf(" %39[^\n]",v.ownerName);

    print_input_prompt("Enter phone number: ");
    scanf(" %14s",v.phone);

    print_input_prompt("Enter model of your vehicle: ");
    scanf(" %29[^\n]",v.model);

    print_input_prompt("Enter type of your vehicle: ");
    scanf(" %9s", v.type);

    print_input_prompt("Enter Year: ");
    scanf("%d",&v.year);


    fp = fopen(VEHICLE_FILE,"ab");
    if(fp == NULL){
        print_error("Unable to open vehicles file");
        return;
    }
    // write the details of vehicles in the file
    fwrite(&v,sizeof(Vehicle),1,fp);
    fclose(fp);

    print_success("Vehicle added successfully");
}

    // Now for viewing vehicles
    void viewVehicles(){
        Vehicle v;
        FILE *fp;

        fp = fopen(VEHICLE_FILE,"rb");

        if(fp == NULL){
            print_error("No vehicles found");
            return;
        }

        print_header("VEHICLE LIST");

        while(fread(&v,sizeof(Vehicle),1,fp)){
            printf("\n");
            print_divider();
            printf(" Vehicle No   : %s\n", v.vehicleNo);
            printf(" Owner Name   : %s\n",v.ownerName);
            printf(" Phone Number : %s\n",v.phone);
            printf(" Model        : %s\n",v.model);
            printf(" Type         : %s\n",v.type);
            printf(" Year         : %d\n",v.year);
            print_divider();
        }

        fclose(fp);
        wait_for_enter();
    }
        // Now for searching vehicles
        
    void searchVehicle(){
        Vehicle v;
        int found = 0;
        char searchedNo[VEHICLE_NO_LEN];
        FILE *fp;
        
        print_subheader("SEARCH VEHICLE");
        print_input_prompt("Enter Vehicle No: ");
        scanf(" %19s",searchedNo);

        
        fp = fopen(VEHICLE_FILE,"rb");


        if(fp == NULL){
            print_error("No vehicle records exist");
            return;
        }
        while(fread(&v,sizeof(Vehicle),1,fp)){
            if(strcmp(searchedNo,v.vehicleNo)==0){
                found = 1;
                printf("\n");
                print_divider();
                printf(" Owner Name   : %s\n",v.ownerName);
                printf(" Phone Number : %s\n",v.phone);
                printf(" Model        : %s\n",v.model);
                printf(" Type         : %s\n",v.type);
                printf(" Year         : %d\n",v.year);
                print_divider();
                break;
        }
         
    
     }

                if(found == 0){
                print_error("Vehicle not found");
                }

                fclose(fp);
                wait_for_enter();
 }

// Function to update vehicle details
void updateVehicle() {
    Vehicle v;
    FILE *fp;
    int found = 0;
    char updateNo[VEHICLE_NO_LEN];

    print_subheader("UPDATE VEHICLE DETAILS");
    print_input_prompt("Enter Vehicle No to update: ");
    scanf(" %19s", updateNo);

    fp = fopen(VEHICLE_FILE, "rb+");
    if (fp == NULL) {
        print_error("Unable to open vehicle file!");
        return;
    }

    while(fread(&v, sizeof(Vehicle), 1, fp)) {
        if(strcmp(v.vehicleNo, updateNo) == 0) {
            found = 1;
            print_info("Vehicle found! Enter new details.");
            
            // Skip updating Vehicle No (Primary Key effectively)
            // Or allow it? Usually safer not to change ID, but here VehicleNo is the ID.
            // Let's keep VehicleNo same to avoid confusion, or allow change if user wants.
            // Requirement says "update vehicle", implies details.
            
            print_input_prompt("Enter New Owner Name: ");
            scanf(" %39[^\n]", v.ownerName);
            
            print_input_prompt("Enter New Phone Number: ");
            scanf(" %14s", v.phone);
            
            print_input_prompt("Enter New Model: ");
            scanf(" %29[^\n]", v.model);
            
            print_input_prompt("Enter New Type: ");
            scanf(" %9s", v.type);
            
            print_input_prompt("Enter New Year: ");
            scanf("%d", &v.year);

            // Move pointer back to start of this record
            fseek(fp, -sizeof(Vehicle), SEEK_CUR);
            fwrite(&v, sizeof(Vehicle), 1, fp);
            break;
        }
    }
    
    fclose(fp);

    if(found) {
        print_success("Vehicle details updated successfully!");
    } else {
        print_error("Vehicle not found!");
    }
    wait_for_enter();
}

// Function to delete a vehicle
void deleteVehicle() {
    Vehicle v;
    FILE *fp, *tempFp;
    int found = 0;
    char deleteNo[VEHICLE_NO_LEN];

    print_subheader("DELETE VEHICLE");
    print_input_prompt("Enter Vehicle No to delete: ");
    scanf(" %19s", deleteNo);

    fp = fopen(VEHICLE_FILE, "rb");
    if (fp == NULL) {
        print_error("Unable to open vehicle file!");
        return;
    }

    tempFp = fopen("data/temp_vehicles.dat", "wb");
    if (tempFp == NULL) {
        fclose(fp);
        print_error("Unable to create temporary file!");
        return;
    }

    while(fread(&v, sizeof(Vehicle), 1, fp)) {
        if(strcmp(v.vehicleNo, deleteNo) == 0) {
            found = 1;
        } else {
            fwrite(&v, sizeof(Vehicle), 1, tempFp);
        }
    }

    fclose(fp);
    fclose(tempFp);

    if(found) {
        remove(VEHICLE_FILE);
        rename("data/temp_vehicles.dat", VEHICLE_FILE);
        print_success("Vehicle deleted successfully!");
    } else {
        remove("data/temp_vehicles.dat");
        print_error("Vehicle not found!");
    }
    wait_for_enter();
}


//  Now we gonna write the function for vehicle management menu


    void vehicleMenu(){
        int choice;
        

        while(1){

            print_header("VEHICLE MANAGEMENT");
            
            print_menu_item(1, "Add Vehicles");
            print_menu_item(2, "View Vehicles");
            print_menu_item(3, "Search Vehicles");
            print_menu_item(4, "Update Vehicle");
            print_menu_item(5, "Delete Vehicle");
            print_menu_item(6, "Return to Main Menu");
            
            printf("\n");
            print_input_prompt("Enter your choice: ");
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
                updateVehicle();
                break;

                case 5:
                deleteVehicle();
                break;

                case 6:
                return;

                default:
                print_error("Invalid Choice. Choose again!");
                break;

            }

        }
    }


    
    
