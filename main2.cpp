#include <bits/stdc++.h>
using namespace std;

// ---------- Driver and Rider Structures ----------
struct Driver {
    int id;
    vector<int> route; // list of location IDs on the route
};

struct Rider {
    int currentLocation;
    int destination;
};

// ---------- Graph Class ----------
class RouteGraph {
private:
    unordered_map<int, vector<int>> adj;

public:
    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u); // undirected
    }

    // BFS to get the shortest path from src to dest
    vector<int> shortestPath(int src, int dest) {
        unordered_map<int, int> parent;
        unordered_set<int> visited;
        queue<int> q;

        q.push(src);
        visited.insert(src);
        parent[src] = -1;

        while (!q.empty()) {
            int curr = q.front(); q.pop();
            if (curr == dest) break;

            for (int neighbor : adj[curr]) {
                if (!visited.count(neighbor)) {
                    visited.insert(neighbor);
                    parent[neighbor] = curr;
                    q.push(neighbor);
                }
            }
        }

        // Build path
        vector<int> path;
        if (!parent.count(dest)) return path; // no path found

        for (int at = dest; at != -1; at = parent[at])
            path.push_back(at);

        reverse(path.begin(), path.end());
        return path;
    }

    // Add all drivers' routes to graph
    void buildFromDriverRoutes(const vector<Driver>& drivers) {
        for (const auto& driver : drivers) {
            const vector<int>& route = driver.route;
            for (int i = 1; i < route.size(); ++i) {
                addEdge(route[i - 1], route[i]);
            }
        }
    }
};

// ---------- Ride Matcher ----------
class RideMatcher {
public:
    int findBestDriver(const vector<Driver>& drivers, const Rider& rider) {
        RouteGraph graph;
        graph.buildFromDriverRoutes(drivers);

        vector<int> riderPath = graph.shortestPath(rider.currentLocation, rider.destination);
        if (riderPath.empty()) {
            cout << "No path found from rider's location to destination.\n";
            return -1;
        }

        unordered_set<int> pathSet(riderPath.begin(), riderPath.end());

        int bestDriverId = -1;
        int maxOverlap = 0;

        for (const auto& driver : drivers) {
            int overlap = 0;
            for (int point : driver.route) {
                if (pathSet.count(point)) overlap++;
            }
            if (overlap > maxOverlap) {
                maxOverlap = overlap;
                bestDriverId = driver.id;
            }
        }

        return bestDriverId;
    }
};

// ---------- Main Function for Testing ----------
int main() {
    // Sample drivers
    vector<Driver> drivers = {
        {1, {1, 2, 3, 4, 5}},
        {2, {6, 7, 3, 8, 9}},
        {3, {10, 11, 4, 12}},
        {4, {13, 14, 15, 5}}
    };

    // Sample rider
    Rider rider = {1, 12}; // start at node 1, end at node 12

    RideMatcher matcher;
    int bestDriverId = matcher.findBestDriver(drivers, rider);

    if (bestDriverId != -1) {
        cout << "Best driver for the rider is: Driver " << bestDriverId << endl;
    } else {
        cout << "No suitable driver found.\n";
    }

    return 0;
}
