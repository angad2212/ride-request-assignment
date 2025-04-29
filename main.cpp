#include <bits/stdc++.h>
using namespace std;

//Structs and Classes

//a point/location (x, y)
struct Point {
    double x, y;
    Point(double x = 0.0, double y = 0.0) : x(x), y(y) {}
};

//a Driver
struct Driver {
    int id;
    Point location;
    double speed; // in km/h

    Driver(int id, Point location, double speed)
        : id(id), location(location), speed(speed) {}
};

//a Rider
struct Rider {
    int id;
    Point location;

    Rider(int id, Point location) : id(id), location(location) {}
};

//a Ride Request (for scheduling rides)
struct RideRequest {
    Rider rider;
    string scheduledTime; // Format: "HH:MM"

    RideRequest(Rider rider, string scheduledTime)
        : rider(rider), scheduledTime(scheduledTime) {} //member initialiser
};

//Helper Functions

//euclidean distance between two points
double calculateDistance(Point a, Point b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

//calculate fare
double calculateFare(double distance) {
    const double baseFare = 50.0; 
    const double farePerKm = 10.0; 
    return baseFare + (farePerKm * distance);
}

//calculate ETA given distance and driver's speed
double calculateETA(double distance, double speed) {
    if (speed == 0) return -1; // Avoid division by zero
    return distance / speed; // returns time in hours
}

//Main Ride System Class

class RideSystem {
private:
    vector<Driver> drivers; //list of available drivers
    queue<RideRequest> scheduledRides; //queue for scheduled rides
    unordered_map<int, vector<Point>> driverRoutes; //driver ID -> list of waypoints (route)
    //hashmap (key: value)

public:
    //ddd a driver to the system
    void addDriver(Driver driver) {
        drivers.push_back(driver);
    }

    //view a driver's planned route
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

    //schedule a future ride
    void scheduleRide(Rider rider, string scheduledTime) {
        RideRequest request(rider, scheduledTime);
        scheduledRides.push(request);
        cout << "Ride scheduled for Rider ID " << rider.id << " at " << scheduledTime << ".\n";
    }

    //assign the nearest driver to a rider
    //Dijkstra approach with a greedy algo 
    Driver findNearestDriver(Rider rider) {
      if (drivers.empty()) {
          throw runtime_error("No drivers available!");
      }

      //min-Heap based on distance
      priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;

      for (auto& driver : drivers) {
          double dist = calculateDistance(driver.location, rider.location);
          pq.push({dist, driver.id});
      }

      int nearestDriverId = pq.top().second;

      //find and return the driver object
      for (auto& driver : drivers) {
          if (driver.id == nearestDriverId) {
              return driver;
          }
      }

      //if somehow not found (should not happen)
      throw runtime_error("Nearest driver not found!");
    }


    //handle immediate ride request (assign driver, calculate fare and ETA and stuff)
    void assignRide(Rider rider) {
        try {
            Driver nearestDriver = findNearestDriver(rider);
            double distance = calculateDistance(nearestDriver.location, rider.location);
            double fare = calculateFare(distance);
            double etaHours = calculateETA(distance, nearestDriver.speed);
            double etaMinutes = etaHours * 60; 

            cout << "Assigned Driver ID: " << nearestDriver.id << endl;
            cout << "Distance to Rider: " << distance << " km" << endl;
            cout << "Estimated Fare: $" << fare << endl;
            cout << "Estimated Time of Arrival: " << etaMinutes << " minutes" << endl;

            //update driver location to rider location after assigned
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

    //process all scheduled rides
    void processScheduledRides() {
        cout << "Processing Scheduled Rides" << endl;
        while (!scheduledRides.empty()) {
            RideRequest req = scheduledRides.front();
            scheduledRides.pop();

            cout << "\nScheduled Ride at " << req.scheduledTime << ":\n";
            assignRide(req.rider);
        }
    }

    //adding a route for a driver
    void addRouteToDriver(int driverId, vector<Point> route) {
        driverRoutes[driverId] = route;
    }
};

//Main Simulation

int main() {
    RideSystem system;

    //adding some drivers
    system.addDriver(Driver(1, Point(0, 0), 40)); // Driver 1 at (0, 0) with speed 40
    system.addDriver(Driver(2, Point(5, 5), 50)); // Driver 2 at (5,5) with speed 50
    system.addDriver(Driver(3, Point(10, -3), 60)); // Driver 3 at (10,-3) with speed 60

    //simulate Driver Routes
    system.addRouteToDriver(1, {Point(0,0), Point(2,2), Point(4,4)}); //hashmap: key-> 1: value: (0,0) (2,2) (4,4)
    system.addRouteToDriver(2, {Point(5,5), Point(6,7)});
    
    //sdding a rider
    Rider rider1(1001, Point(1, 1)); // Rider id 1001 at position 1,1

    cout << "Immediate Ride Request" << endl;
    system.assignRide(rider1); //akarsh has been assigned with angad

    //scheduling future rides
    Rider rider2(1002, Point(7, 8));
    Rider rider3(1003, Point(2, 2));

    system.scheduleRide(rider2, "17:30");
    system.scheduleRide(rider3, "18:15");

    //view Driver Route
    cout << "Driver Routes" << endl;
    system.viewDriverRoute(1);
    system.viewDriverRoute(2);

    //process all scheduled rides
    system.processScheduledRides();

    return 0;
}
