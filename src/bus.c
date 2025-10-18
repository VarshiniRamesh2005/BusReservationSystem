#include <stdio.h>
#include <string.h>
#include "bus.h"

Bus buses[MAX_BUSES];

void initBuses() {
    for(int i=0;i<MAX_BUSES;i++){
        buses[i].busNo = 100 + i;
        sprintf(buses[i].source,"City%c",'A'+i);
        sprintf(buses[i].destination,"City%c",'B'+i);
        buses[i].totalSeats = MAX_SEATS;
        buses[i].availableSeats = MAX_SEATS;
        memset(buses[i].seats,0,sizeof(buses[i].seats));
        buses[i].fareRegular = 150 + i*20;
        buses[i].farePremium = buses[i].fareRegular * 2;
    }
}

void displayBuses(){
    printf("\nBusNo  Source     Destination  Total Seats  Avail Seats  Fare(R/P)\n");
    for(int i=0;i<MAX_BUSES;i++){
        printf("%d    %-10s %-10s %-12d %-12d %d/%d\n",
            buses[i].busNo, buses[i].source, buses[i].destination,
            buses[i].totalSeats, buses[i].availableSeats,
            buses[i].fareRegular, buses[i].farePremium);
    }
}

void displaySeatMap(int busNo){
    int found=0;
    for(int i=0;i<MAX_BUSES;i++){
        if(buses[i].busNo==busNo){
            found=1;
            printf("\nSeat Map (O=Available, X=Booked):\n");
            for(int s=0;s<MAX_SEATS;s++){
                printf("%c ", buses[i].seats[s]==0?'O':'X');
                if((s+1)%8==0) printf("\n");
            }
            printf("\n");
            break;
        }
    }
    if(!found) printf("Bus not found!\n");
}
