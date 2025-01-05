// MetroMap.h
#ifndef METRO_MAP_H
#define METRO_MAP_H

#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
#include <limits>
#include <algorithm> // Required for std::remove_if

struct Edge {
    std::string destination;
    int cost;
    int time;
};

struct PathResult {
    std::vector<std::string> path;
    int cost = 0;
    int time = 0;
};

class MetroMap {
private:
    std::unordered_map<std::string, std::vector<Edge>> adjacencyList;

    // Helper function to find shortest path using Dijkstra's Algorithm
    PathResult findShortestPath(const std::string& start, const std::string& end, bool byCost) {
        std::unordered_map<std::string, int> distances;
        std::unordered_map<std::string, std::string> previous;
        auto compare = [&](const std::pair<int, std::string>& a, const std::pair<int, std::string>& b) {
            return a.first > b.first;
        };
        std::priority_queue<std::pair<int, std::string>, std::vector<std::pair<int, std::string>>, decltype(compare)> pq(compare);

        for (const auto& station : adjacencyList) {
            distances[station.first] = std::numeric_limits<int>::max();
        }
        distances[start] = 0;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [currentDistance, currentStation] = pq.top();
            pq.pop();

            if (currentStation == end) break;

            for (const auto& edge : adjacencyList[currentStation]) {
                int weight = byCost ? edge.cost : edge.time;
                int newDistance = currentDistance + weight;

                if (newDistance < distances[edge.destination]) {
                    distances[edge.destination] = newDistance;
                    previous[edge.destination] = currentStation;
                    pq.push({newDistance, edge.destination});
                }
            }
        }

        PathResult result;
        if (distances[end] == std::numeric_limits<int>::max()) return result;

        for (std::string at = end; !at.empty(); at = previous[at]) {
            result.path.insert(result.path.begin(), at);
        }

        result.cost = byCost ? distances[end] : 0;
        result.time = byCost ? 0 : distances[end];

        return result;
    }

public:
    void initializeMetroMap() {
        // List of stations
        std::vector<std::string> stations = {
            "Jhil Mil", "DLF Phase 3", "Okhla NSIC", "Dwarka Mor", "Dilli Haat INA [Conn: Yellow]", 
            "Noida Sector 143", "Moolchand", "Chawri Bazar", "Maya Puri", 
            "Central Secretariat [Conn: Violet]", "Noida Sector 146", "Tikri Border", 
            "Jangpura", "Major Mohit Sharma", "Majlis Park", "Bhikaji Cama Place", 
            "Mundka Industrial Area (MIA)", "Belvedere Towers", "Adarsh Nagar", 
            "Noida City Center", "Arjan Garh", "Dwarka Sector 9", "Azadpur [Conn: Yellow]", 
            "Qutab Minar", "R K Ashram Marg", "Uttam Nagar West", "Dwarka [Conn: Blue]", 
            "Delta 1 Greater Noida", "Golf Course", "Shiv Vihar", "Kashmere Gate [Conn: Yellow]", 
            "Jawaharlal Nehru Stadium", "Patel Chowk", "Janak Puri West [Conn: Magenta]", 
            "Kalkaji Mandir [Conn: Violet]", "Dwarka Sector 21(First station) [Conn: Orange]", 
            "Subhash Nagar", "Tughlakabad", "Old Faridabad", "Rohini Sector 18-19", 
            "Keshav Puram", "Kohat Enclave", "Paschim Vihar (West)", "Dwarka Sector 14", 
            "IIT Delhi", "Rajouri Garden [Conn: Blue]", "Karkarduma Court", 
            "Rajendra Place", "Hauz Khas [Conn: Yellow]", "Noida Sector 137", 
            "Okhla", "Jhandewalan", "Raj Bagh", "Inderlok Conn:Red", "Noida Sector 51 [Conn: Blue]", 
            "Pari Chowk Greater Noida", "Noida Sector 148", "Pitam Pura", "Moti Nagar"
        };

        // Adding stations to the metro map
        for (const auto& station : stations) {
            addStation(station);
        }

        // Adding connections (distances and costs are placeholders)
        addEdge("Jhil Mil", "DLF Phase 3", 10, 15);
        addEdge("DLF Phase 3", "Okhla NSIC", 20, 25);
        addEdge("Okhla NSIC", "Dwarka Mor", 15, 20);
        addEdge("Dwarka Mor", "Dilli Haat INA [Conn: Yellow]", 30, 40);
        // Add more edges as needed...
    }

    void addStation(const std::string& name) {
        if (adjacencyList.find(name) == adjacencyList.end()) {
            adjacencyList[name] = {};
        }
    }

    bool removeStation(const std::string& name) {
        if (adjacencyList.erase(name) == 0) return false;

        for (auto& [station, edges] : adjacencyList) {
            edges.erase(std::remove_if(edges.begin(), edges.end(), [&](const Edge& edge) {
                return edge.destination == name;
            }), edges.end());
        }
        return true;
    }

    void addEdge(const std::string& from, const std::string& to, int cost, int time) {
        adjacencyList[from].push_back({to, cost, time});
        adjacencyList[to].push_back({from, cost, time});
    }

    PathResult findShortestPathByCost(const std::string& start, const std::string& end) {
        return findShortestPath(start, end, true);
    }

    PathResult findShortestPathByTime(const std::string& start, const std::string& end) {
        return findShortestPath(start, end, false);
    }
};

#endif // METRO_MAP_H
