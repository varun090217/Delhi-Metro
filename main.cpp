// main.cpp
#include <iostream>
#include "MetroMap.h"

void adminMenu(MetroMap& metroMap) {
    std::string username, password;
    std::cout << "Admin Login:\nUsername: ";
    std::cin >> username;
    std::cout << "Password: ";
    std::cin >> password;

    // Placeholder authentication check
    if (username == "admin" && password == "password") {
        std::cout << "Login successful.\n";
        while (true) {
            int choice;
            std::cout << "\nAdmin Menu:\n"
                      << "1. Add Station\n"
                      << "2. Remove Station\n"
                      << "3. Logout\n"
                      << "Enter your choice: ";
            std::cin >> choice;

            if (choice == 1) {
                std::string stationName;
                std::cout << "Enter station name to add: ";
                std::cin.ignore();
                std::getline(std::cin, stationName);
                metroMap.addStation(stationName);
                std::cout << "Station added successfully.\n";
            } else if (choice == 2) {
                std::string stationName;
                std::cout << "Enter station name to remove: ";
                std::cin.ignore();
                std::getline(std::cin, stationName);
                if (metroMap.removeStation(stationName)) {
                    std::cout << "Station removed successfully.\n";
                } else {
                    std::cout << "Station not found.\n";
                }
            } else if (choice == 3) {
                std::cout << "Logging out...\n";
                break;
            } else {
                std::cout << "Invalid choice. Try again.\n";
            }
        }
    } else {
        std::cout << "Invalid credentials. Returning to main menu.\n";
    }
}

void userMenu(MetroMap& metroMap) {
    while (true) {
        int choice;
        std::cout << "\nUser Menu:\n"
                  << "1. Find Shortest Path by Cost\n"
                  << "2. Find Shortest Path by Time\n"
                  << "3. Exit\n"
                  << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1 || choice == 2) {
            std::string start, end;
            std::cout << "Enter starting station: ";
            std::cin.ignore();
            std::getline(std::cin, start);
            std::cout << "Enter destination station: ";
            std::getline(std::cin, end);

            PathResult result = (choice == 1) 
                ? metroMap.findShortestPathByCost(start, end) 
                : metroMap.findShortestPathByTime(start, end);

            if (result.path.empty()) {
                std::cout << "No path found between " << start << " and " << end << ".\n";
            } else {
                std::cout << "Shortest Path: ";
                for (const auto& station : result.path) {
                    std::cout << station << " ";
                }
                std::cout << "\n" 
                          << (choice == 1 ? "Cost: " : "Time: ") 
                          << (choice == 1 ? result.cost : result.time) << "\n";
            }
        } else if (choice == 3) {
            std::cout << "Exiting user menu...\n";
            break;
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }
}

int main() {
    MetroMap metroMap;
    metroMap.initializeMetroMap();

    while (true) {
        int role;
        std::cout << "\nWelcome to the Metro System!\n"
                  << "1. Admin\n"
                  << "2. User\n"
                  << "3. Exit\n"
                  << "Enter your choice: ";
        std::cin >> role;

        if (role == 1) {
            adminMenu(metroMap);
        } else if (role == 2) {
            userMenu(metroMap);
        } else if (role == 3) {
            std::cout << "Exiting the application. Goodbye!\n";
            break;
        } else {
            std::cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
