#include <stdio.h>
#include <stdlib.h>
#include "bus.h"
#include "booking.h"

int main(){
    int choice;
    initBuses();

    while(1){
        printf("\n--- Bus Reservation System ---\n");
        printf("1. View Buses\n");
        printf("2. View Seat Map\n");
        printf("3. Book Ticket\n");
        printf("4. View Bookings\n");
        printf("5. Search Passenger\n");
        printf("6. Cancel Ticket\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d",&choice);

        switch(choice){
            case 1: displayBuses(); break;
            case 2: {
                int busNo;
                printf("Enter Bus Number to display seat map: ");
                scanf("%d",&busNo);
                displaySeatMap(busNo);
                break;
            }
            case 3: bookTicket(); break;
            case 4: viewBookings(); break;
            case 5: searchPassenger(); break;
            case 6: cancelTicket(); break;
            case 7: exit(0);
            default: printf("Invalid choice!\n");
        }
    }
    return 0;
}
