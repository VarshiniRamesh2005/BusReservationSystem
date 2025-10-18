# Advanced Bus Reservation System (C)
## Description

A console-based application to manage bus ticket bookings with multiple seat support, passenger details, cancellations, and logging.

---

## Features

* View all buses with available seats and fares
* View seat map for each bus
* Book multiple tickets at once (Regular/Premium seats)
* Cancel booked tickets
* Search passengers by name
* Persistent storage in `data/bookings.txt`
* Logs stored in `data/logs.txt`
* Neat console tables for better readability

---

## Requirements

* C compiler (GCC recommended)
* Windows/Linux/Mac terminal or command prompt

---

## How to Run

1. Open terminal/PowerShell and navigate to project folder.

2. Ensure `data/` folder exists (optional, program creates files automatically):

   ```bash
   mkdir data
   ```

3. Compile all source files:

   ```bash
   gcc src/*.c -o BusReservation -std=c99 -Wall -Wextra -mconsole
   ```

4. Run the program:

   ```bash
   ./BusReservation      # Linux/Mac
   .\BusReservation.exe  # Windows
   ```

5. Follow the on-screen menu to view buses, book tickets, cancel, or search passengers.

---

## Booking Flow

1. Select **Book Ticket** from the menu.
2. Enter **Bus Number**.
3. Enter **number of seats** to book.
4. For each seat, enter:

   * Name
   * Age
   * Phone
   * Seat Class (Regular/Premium)
5. Tickets are saved in `data/bookings.txt`.
6. Logs are saved in `data/logs.txt` (summary only).

---

## Learnings

* Modular C programming using structs and arrays
* File handling for persistent storage
* Logging and tracking actions
* Multi-seat booking with dynamic input
* Console-based UI design and formatting

---

## Future Enhancements

* Allow users to pick specific seat numbers instead of first available
* GUI version using C++ or Java Swing
* Online booking system with database backend
* Email/SMS notifications for bookings

---

