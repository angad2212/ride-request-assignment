#include <bits/stdc++.h>
using namespace std;

//  Structs and Classes

// Represents a point/location (x, y)
struct Point {
    double x, y;
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
};

// Represents a Driver
struct Driver {
    int id;
    Point location;
    double speed; // in km/h

    Driver(int id, Point location, double speed)
        : id(id), location(location), speed(speed) {}
};

// Represents a Rider
struct Rider {
    int id;
    Point location;

    Rider(int id, Point location) : id(id), location(location) {}
};

// Represents a Ride Request (for scheduling rides)
struct RideRequest {
    Rider rider;
    string scheduledTime; // Format: "HH:MM"

    RideRequest(Rider rider, string scheduledTime)
        : rider(rider), scheduledTime(scheduledTime) {}
};

//  Helper Functions

// Calculate Euclidean distance between two points
double calculateDistance(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

// Calculate fare given distance
double calculateFare(double distance) {
    const double baseFare = 50.0; // Base Fare
    const double farePerKm = 10.0; // Fare per km
    return baseFare + (farePerKm * distance);
}

// Calculate ETA given distance and driver's speed
double calculateETA(double distance, double speed) {
    if (speed == 0) return -1; // Avoid division by zero
    return distance / speed; // returns time in hours
}

//  Main Ride System Class

class RideSystem {
private:
    vector<Driver> drivers; // List of available drivers
    queue<RideRequest> scheduledRides; // Queue for scheduled rides
    unordered_map<int, vector<Point>> driverRoutes; // Driver ID -> list of waypoints (route)

public:
    // Add a driver to the system
    void addDriver(Driver driver) {
        drivers.push_back(driver);
    }

    // View a driver's planned route
    void viewDriverRoute(int driverId) {
        if (driverRoutes.find(driverId) == driverRoutes.end()) {
            cout << "No routes found for Driver ID " << driverId << ".\n";
            return;
        }
        cout << "Route for Driver ID " << driverId << ":\n";
        for (auto& point : driverRoutes[driverId]) {
            cout << "(" << point.x << ", " << point.y << ") -> ";
        }
        cout << "END\n";
    }

    // Schedule a future ride
    void scheduleRide(Rider rider, string scheduledTime) {
        RideRequest request(rider, scheduledTime);
        scheduledRides.push(request);
        cout << "Ride scheduled for Rider ID " << rider.id << " at " << scheduledTime << ".\n";
    }

    // Assign the nearest driver to a rider
    // Assign the nearest driver to a rider
  Driver findNearestDriver(Rider rider) {
    if (drivers.empty()) {
        throw runtime_error("No drivers available!");
    }

    // Min-Heap based on distance
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

    for (auto& driver : drivers) {
        double dist = calculateDistance(driver.location, rider.location);
        pq.push({dist, driver.id});
    }

    int nearestDriverId = pq.top().second;

    // Find and return the driver object
    for (auto& driver : drivers) {
        if (driver.id == nearestDriverId) {
            return driver;
        }
    }

    // If somehow not found (should not happen)
    throw runtime_error("Nearest driver not found!");
  }


    // Handle immediate ride request (assign driver, calculate fare and ETA)
    void assignRide(Rider rider) {
        try {
            Driver nearestDriver = findNearestDriver(rider);
            double distance = calculateDistance(nearestDriver.location, rider.location);
            double fare = calculateFare(distance);
            double etaHours = calculateETA(distance, nearestDriver.speed);
            double etaMinutes = etaHours * 60; // Convert hours to minutes

            cout << "Assigned Driver ID: " << nearestDriver.id << "\n";
            cout << "Distance to Rider: " << distance << " km\n";
            cout << "Estimated Fare: ₹" << fare << "\n";
            cout << "Estimated Time of Arrival: " << etaMinutes << " minutes\n";

            // Update driver location to rider location after assignment (simulating pickup)
            for (auto& driver : drivers) {
                if (driver.id == nearestDriver.id) {
                    driver.location = rider.location;
                    break;
                }
            }
        } catch (exception& e) {
            cout << "Error: " << e.what() << endl;
        }
    }

    // Process all scheduled rides
    void processScheduledRides() {
        cout << "\nProcessing Scheduled Rides...\n";
        while (!scheduledRides.empty()) {
            RideRequest req = scheduledRides.front();
            scheduledRides.pop();

            cout << "\nScheduled Ride at " << req.scheduledTime << ":\n";
            assignRide(req.rider);
        }
    }

    // Simulate adding a route for a driver
    void addRouteToDriver(int driverId, vector<Point> route) {
        driverRoutes[driverId] = route;
    }
};

//  Main Simulation

int main() {
    RideSystem system;

    // Adding some drivers
    system.addDriver(Driver(1, Point(0, 0), 40)); // Driver 1 at (0, 0)
    system.addDriver(Driver(2, Point(5, 5), 50)); // Driver 2 at (5,5)
    system.addDriver(Driver(3, Point(10, -3), 60)); // Driver 3 at (10,-3)

    // Simulate Driver Routes
    system.addRouteToDriver(1, {Point(0,0), Point(2,2), Point(4,4)});
    system.addRouteToDriver(2, {Point(5,5), Point(6,7)});
    
    // Adding a rider
    Rider rider1(1001, Point(1, 1));

    cout << "\n--- Immediate Ride Request ---\n";
    system.assignRide(rider1);

    // Scheduling future rides
    Rider rider2(1002, Point(7, 8));
    Rider rider3(1003, Point(2, 2));

    system.scheduleRide(rider2, "17:30");
    system.scheduleRide(rider3, "18:15");

    // View Driver Route
    cout << "\n--- Driver Routes ---\n";
    system.viewDriverRoute(1);
    system.viewDriverRoute(2);

    // Process all scheduled rides
    system.processScheduledRides();

    return 0;
}
