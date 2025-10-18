#ifndef BUS_H
#define BUS_H

#define MAX_BUSES 5
#define MAX_SEATS 40

typedef struct {
    int busNo;
    char source[20];
    char destination[20];
    int totalSeats;
    int availableSeats;
    int seats[MAX_SEATS]; // 0=available,1=booked
    int fareRegular;
    int farePremium;
} Bus;

extern Bus buses[MAX_BUSES];

void initBuses();
void displayBuses();
void displaySeatMap(int busNo);

#endif
