#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../include/service.h"
#include "../include/ui.h"

#define SERVICE_FILE "data/services.dat"


// Writing function for add service
void addService(){
    Service s;
    FILE *fp;
    print_header("ADD NEW SERVICE RECORD");

    // taking input

    print_input_prompt("Enter Service ID: ");
    scanf("%d",&s.serviceId);
    print_input_prompt("Enter vehicle NO: ");
    scanf(" %19s",s.vehicleNo);
    print_input_prompt("Enter Service Description: ");
    scanf(" %39[^\n]",s.description);
    print_input_prompt("Enter Service Cost: ");
    scanf("%d",&s.cost);
    strcpy(s.status,"Pending");

    fp = fopen(SERVICE_FILE,"ab");
    if(fp == NULL){
        print_error("Unable to open service file");
        return;
    }
    
    // writing the service details in service.dat file

    fwrite(&s,sizeof(Service),1,fp);
    fclose(fp);

    print_success("Service record added successfuly!");
}
// Now writing function to view services 
void viewServices(){
    Service s;
    FILE *fp;

    fp = fopen(SERVICE_FILE,"rb");

    if(fp == NULL){
        print_error("No Service Records found");
        return;
    }

    print_header("SERVICE RECORDS");

    while(fread(&s,sizeof(Service),1,fp)){
        printf("\n");
        print_divider();
        printf(" Service ID   : %d\n",s.serviceId);
        printf(" Vehicle No   : %s\n",s.vehicleNo);
        printf(" Description  : %s\n",s.description);
        printf(" Cost         : %d\n",s.cost);
        if(strcmp(s.status, "Pending") == 0) {
            printf(" Status       : %s%s%s\n", COLOR_YELLOW, s.status, COLOR_RESET);
        } else {
            printf(" Status       : %s%s%s\n", COLOR_GREEN, s.status, COLOR_RESET);
        }
        print_divider();
    }

    fclose(fp);
    wait_for_enter();

}

// Now writing the function to search vehicle by number

void searchServiceByVehicle(){
    Service s;
    FILE *fp;
    int found = 0;
    char searchedNo[VEHICLE_NO_LEN];

    print_subheader("SEARCH SERVICE HISTORY");
    print_input_prompt("Enter Vehicle No: ");
    scanf(" %19s",searchedNo);

    fp = fopen(SERVICE_FILE,"rb");

    if(fp == NULL){
        print_error("No service records exist");
        return;
    }

    while(fread(&s,sizeof(Service),1,fp)){
        if(strcmp(searchedNo,s.vehicleNo)==0){
            found = 1;
        printf("\n");
        print_divider();
        printf(" Service ID   : %d\n",s.serviceId);
        printf(" Description  : %s\n",s.description);
        printf(" Cost         : %d\n",s.cost);
        printf(" Status       : %s\n",s.status);
        print_divider();

        }
    }

    if(found == 0){
        print_error("No service record is found with your given number");
    }

    fclose(fp);
    wait_for_enter();
}

// writing function to update service status

void updateServiceStatus(){
    Service s;
    FILE *fp;
    int serviceIDToUpdate;
    int found = 0;

    print_subheader("UPDATE SERVICE STATUS");
    print_input_prompt("Enter Service ID to update status: ");
    scanf("%d",&serviceIDToUpdate);

    fp = fopen(SERVICE_FILE,"rb+");

    if(fp == NULL){
        print_error("No service records found");
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
        print_success("Service Status updated successfully!");
    }
    else{
        print_error("Service ID not found");
    }

    fclose(fp);
}

// Function to delete a service record
void deleteService() {
    Service s;
    FILE *fp, *tempFp;
    int found = 0;
    int deleteId;

    print_subheader("DELETE SERVICE RECORD");
    print_input_prompt("Enter Service ID to delete: ");
    scanf("%d", &deleteId);

    fp = fopen(SERVICE_FILE, "rb");
    if (fp == NULL) {
        print_error("Unable to open service file!");
        return;
    }

    tempFp = fopen("data/temp_services.dat", "wb");
    if (tempFp == NULL) {
        fclose(fp);
        print_error("Unable to create temporary file!");
        return;
    }

    while(fread(&s, sizeof(Service), 1, fp)) {
        if(s.serviceId == deleteId) {
            found = 1;
        } else {
            fwrite(&s, sizeof(Service), 1, tempFp);
        }
    }

    fclose(fp);
    fclose(tempFp);

    if(found) {
        remove(SERVICE_FILE);
        rename("data/temp_services.dat", SERVICE_FILE);
        print_success("Service record deleted successfully!");
    } else {
        remove("data/temp_services.dat");
        print_error("Service ID not found!");
    }
    wait_for_enter();
}



// Now writing service management menu

void serviceMenu(){

    int choice;

    while(1){
        print_header("SERVICE MANAGEMENT");
        
        print_menu_item(1, "Add Service Record");
        print_menu_item(2, "View Service Records");
        print_menu_item(3, "Search Service by Vehicle No");
        print_menu_item(4, "Update Service Status");
        print_menu_item(5, "Delete Service Record");
        print_menu_item(6, "Return to Main Menu");

        printf("\n");
        print_input_prompt("Enter your choice: ");
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
            deleteService();
            break;

            case 6:
            return; // goes back to main menu

            default:
            print_error("Invalid choice. Try again.");
        }
    }


}