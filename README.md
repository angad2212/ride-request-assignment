# 🚗 Ride Assign System

A streamlined C++ project simulating a ride-hailing service, focusing on efficient driver assignment and ride management. Demonstrates core software engineering principles and practical application of data structures.

## 🛠 Features

* **Instant Ride Matching:** Quickly assigns the closest available driver to a rider.
* **Basic Fare Calculation:** Estimates ride cost based on distance.
* **Driver Availability:** Tracks and manages the current location and status of drivers.
* **Simple Request Handling:** Processes ride requests from riders.
* **Clear Output:** Provides immediate feedback on driver assignments and estimated fares.

## 💻 Technologies Used

* **Language:** C++
* **Data Structures:** `vector`, `queue`, `priority_queue`, `unordered_map`

## ⚡ Quick Preview

The system takes rider requests and assigns the nearest available driver, displaying the assigned driver's ID and the calculated fare.

## 📋 How it Works (Simplified)

1.  **Driver Initialization:** Drivers with unique IDs and initial locations are added to the system.
2.  **Ride Request:** A rider submits a request with their pickup and drop-off locations.
3.  **Nearest Driver Search:** The system iterates through available drivers to find the one with the shortest distance to the rider's pickup location.
4.  **Assignment:** The nearest driver is assigned to the ride.
5.  **Fare Calculation:** A simple fare is calculated based on the distance between pickup and drop-off.
6.  **Output:** The system displays the assigned driver's ID and the estimated fare.

## 🎯 Why This Project Matters

* **Core Concepts:** Illustrates fundamental concepts of object-oriented programming and basic algorithm design.
* **Practical Application:** Simulates a real-world scenario, demonstrating problem-solving skills.
* **Foundation for Expansion:** Provides a basic framework that can be extended with more advanced features.

## 🧠 Key Functions

* `addDriver(int driverId, double x, double y)`: Adds a new driver to the system with their ID and coordinates.
* `requestRide(double pickupX, double pickupY, double dropoffX, double dropoffY)`: Processes a new ride request and assigns the nearest driver.
* `calculateDistance(double x1, double y1, double x2, double y2)`: Calculates the Euclidean distance between two points.
* `calculateFare(double distance)`: Calculates a basic fare based on the distance.

## 📣 Final Note

This project provides a concise illustration of a ride request system's core functionality. It emphasizes clarity and simplicity, making it easy to understand and build upon.

