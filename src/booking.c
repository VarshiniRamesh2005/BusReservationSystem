#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bus.h"
#include "booking.h"
#include "utils.h"

#define BOOKING_FILE "data\\bookings.txt"

typedef struct {
    int busNo;
    int seatNo;
    char name[50];
    int age;
    char phone[15];
    char seatClass[10];
} Booking;

void bookTicket() {
    int busNo, seatsToBook;
    
    displayBuses();
    printf("Enter Bus Number: "); 
    scanf("%d", &busNo);

    Bus *busPtr = NULL;
    for(int i=0; i<MAX_BUSES; i++){
        if(buses[i].busNo == busNo){
            busPtr = &buses[i];
            break;
        }
    }
    if(!busPtr){
        printf("Bus not found!\n");
        return;
    }

    printf("How many seats do you want to book? "); 
    scanf("%d", &seatsToBook);

    if(busPtr->availableSeats < seatsToBook){
        printf("Only %d seats are available!\n", busPtr->availableSeats);
        return;
    }

    FILE *fp = safeOpenFile(BOOKING_FILE, "a+");
    int bookedSeats = 0;
    char logMsg[200];

    for(int i=0; i<seatsToBook; i++){
        char name[50], phone[15], seatClass[10];
        int age, seatNo=-1, fare=0;

        printf("\n--- Enter details for Seat %d ---\n", i+1);
        printf("Name: "); scanf("%s", name);
        printf("Age: "); scanf("%d", &age);
        printf("Phone: "); scanf("%s", phone);
        printf("Seat Class (Regular/Premium): "); scanf("%s", seatClass);

        // Find first available seat
        for(int s=0; s<MAX_SEATS; s++){
            if(busPtr->seats[s] == 0){
                busPtr->seats[s] = 1;
                busPtr->availableSeats--;
                seatNo = s+1;
                break;
            }
        }

        if(seatNo == -1){
            printf("No more seats available!\n");
            break;
        }

        fprintf(fp, "%d,%d,%s,%d,%s,%s\n", busNo, seatNo, name, age, phone, seatClass);

        // Calculate fare
        fare = (strcmp(seatClass, "Premium") == 0) ? busPtr->farePremium : busPtr->fareRegular;
        printf("Seat %d booked successfully! Fare: %d\n", seatNo, fare);
        bookedSeats++;
    }

    fclose(fp);

    // Log summary only
    snprintf(logMsg, sizeof(logMsg), "Booked %d seat(s) on Bus %d", bookedSeats, busNo);
    logAction(logMsg);
}

void viewBookings(){
    FILE *fp = safeOpenFile(BOOKING_FILE,"r");
    char line[200];
    printf("\nBusNo  Seat  Name       Age  Phone        Class\n");
    while(fgets(line,sizeof(line),fp)){
        int busNo, seatNo, age;
        char name[50], phone[15], seatClass[10];
        sscanf(line,"%d,%d,%[^,],%d,%[^,],%s",&busNo,&seatNo,name,&age,phone,seatClass);
        printf("%-6d %-5d %-10s %-4d %-12s %-7s\n",busNo,seatNo,name,age,phone,seatClass);
    }
    fclose(fp);
}

void searchPassenger(){
    char searchName[50];
    printf("Enter passenger name to search: "); scanf("%s",searchName);
    FILE *fp = safeOpenFile(BOOKING_FILE,"r");
    char line[200];
    int found=0;
    printf("\nBusNo  Seat  Name       Age  Phone        Class\n");
    while(fgets(line,sizeof(line),fp)){
        int busNo, seatNo, age;
        char name[50], phone[15], seatClass[10];
        sscanf(line,"%d,%d,%[^,],%d,%[^,],%s",&busNo,&seatNo,name,&age,phone,seatClass);
        if(strcmp(name,searchName)==0){
            printf("%-6d %-5d %-10s %-4d %-12s %-7s\n",busNo,seatNo,name,age,phone,seatClass);
            found=1;
        }
    }
    if(!found) printf("Passenger not found!\n");
    fclose(fp);
}

void cancelTicket(){
    int busNo, seatNo;
    printf("Enter Bus Number: "); scanf("%d",&busNo);
    printf("Enter Seat Number: "); scanf("%d",&seatNo);

    FILE *fp = safeOpenFile(BOOKING_FILE,"r");
    FILE *temp = safeOpenFile("data\\temp.txt","w");

    char line[200];
    int found=0;
    char logMsg[200];
    while(fgets(line,sizeof(line),fp)){
        int bNo,sNo,age;
        char name[50], phone[15], seatClass[10];
        sscanf(line,"%d,%d,%[^,],%d,%[^,],%s",&bNo,&sNo,name,&age,phone,seatClass);
        if(bNo==busNo && sNo==seatNo){
            snprintf(logMsg,sizeof(logMsg),"Canceled: Bus %d Seat %d (%s) by %s",bNo,sNo,seatClass,name);
            found=1;
            for(int i=0;i<MAX_BUSES;i++){
                if(buses[i].busNo==bNo){ buses[i].seats[sNo-1]=0; buses[i].availableSeats++; break;}
            }
        } else {
            fprintf(temp,"%s",line);
        }
    }
    fclose(fp); fclose(temp);
    remove(BOOKING_FILE);
    rename("data\\temp.txt",BOOKING_FILE);

    if(found){ logAction(logMsg); printf("Ticket canceled successfully.\n"); }
    else printf("Booking not found!\n");
}
