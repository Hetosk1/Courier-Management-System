# Courier Management System

## Purpose
The **Courier Management System** is designed to facilitate the management of courier deliveries, including both regular and express services. It allows users to add, update, delete, and list couriers while maintaining a clear overview of their status and details.

## Overview
This system is implemented in C++ and leverages object-oriented programming principles. It features a `Courier` class for standard deliveries and an `ExpressCourier` class that extends `Courier` to include additional charges for expedited services. A `CourierManagement` class manages the collection of couriers, providing functionalities to add, update, list, and delete courier records.

## Features
- Add regular and express couriers.
- Update the status of couriers.
- List all couriers with their details.
- Delete couriers from the system.
- Input validation for user entries.

## Setup
To set up the Courier Management System, follow these steps:

1. **Prerequisites**
   - Ensure you have a C++ compiler installed (e.g., g++, clang++).
   - A terminal or command prompt for executing commands.

2. **Clone the Repository**
   ```bash
   git clone <repository-url>
   cd <repository-directory>
   ```

3. **Compile the Code**
   Use the following command to compile the program:
   ```bash
   g++ -o courier_management main.cpp
   ```

4. **Run the Program**
   Execute the compiled program with:
   ```bash
   ./courier_management
   ```

## Usage
Upon running the program, you will be presented with a menu of options:

1. **Add Regular Courier**: Input recipient details, weight, distance, and estimated delivery date.
2. **Add Express Courier**: Similar to adding a regular courier but includes an express charge.
3. **List Couriers**: Displays all added couriers along with their details.
4. **Update Courier Status**: Change the status of a specific courier by ID.
5. **Delete Courier**: Remove a courier from the system using its ID.
6. **Exit**: Terminate the program.

### Example Interaction
```plaintext
--- Courier Management System ---
1. Add Regular Courier
2. Add Express Courier
3. List Couriers
4. Update Courier Status
5. Delete Courier
6. Exit
Enter your choice: 1
```

## Additional Information
- The maximum number of couriers that can be managed is set to 100.
- The cost calculation for regular couriers is based on weight and distance.
- Input validation ensures that user entries are correct before proceeding.

## Contributions
Contributions are welcome! Please fork the repository and submit a pull request with your enhancements or fixes.
