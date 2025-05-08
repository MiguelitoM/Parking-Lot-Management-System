# 🅿️ Parking Management System in C

## 📋 Project Overview

This project is a C-based command-line system developed for the **IAED (Data Structures and Algorithms)** course. It manages multiple parking lots, vehicle entries and exits, and billing, following a set of predefined rules.

The system supports a maximum of 20 car parks and interacts through a series of commands provided line-by-line. Users can create parks, record vehicle activity, view reports, and calculate daily revenues. Special billing rules are applied, including tiered pricing per time interval and exceptions for leap years.

---

## ⚙️ How to Compile and Run

To compile the program:
```bash
gcc -O3 -Wall -Wextra -Werror -Wno-unused-result -o proj1 *.c
```

To run the public test suite:
```bash
cd public-tests
make
```

---

## 🧾 Available Commands

The interpreter accepts the following commands:

- `q`  
  **Quits** the program.

- `p`  
  Without arguments: lists existing parks.  
  With arguments: adds a new parking lot with capacity and pricing model.

- `e <park-name> <license-plate> <date> <time>`  
  Registers a vehicle **entry**.

- `s <park-name> <license-plate> <date> <time>`  
  Registers a vehicle **exit** and prints billing.

- `v <license-plate>`  
  Lists **all park entries and exits** for a given vehicle.

- `f <park-name> [<date>]`  
  Shows **revenue** for a park: a summary by day or detailed billing for a specific date.

- `r <park-name>`  
  **Removes** a parking lot and all associated data.

The program reads commands from standard input and returns output to standard output. It stops only when the command `q` is entered.

---

## 📎 Notes

- Vehicle license plates must follow strict formatting rules.
- Dates and times must follow the chronological order of records.
- Billing is calculated based on tiered 15-minute intervals, capped daily.
- On **February 29**, no charges apply.

