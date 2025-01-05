// UserOperations.h
#ifndef USER_OPERATIONS_H
#define USER_OPERATIONS_H

#include "MetroMap.h"
#include <iostream>
#include <string>

class UserOperations {
public:
    static void handleUserInput(MetroMap& metroMap) {
        std::string startStation, endStation;
        int choice;

        std::cout << "Enter starting station: ";
        std::cin.ignore();
        std::getline(std::cin, startStation);
        std::cout << "Enter destination station: ";
        std::getline(std::cin, endStation);

        std::cout << "Choose your preference:\n";
        std::cout << "1. Minimum Cost\n";
        std::cout << "2. Minimum Time\n";
        std::cin >> choice;

        if (choice == 1) {
            auto result = metroMap.findShortestPathByCost(startStation, endStation);
            if (!result.path.empty()) {
                std::cout << "Route found:\n";
                for (const auto& station : result.path) {
                    std::cout << station << " -> ";
                }
                std::cout << "End\n";
                std::cout << "Total Cost: " << result.cost << "\n";
            } else {
                std::cout << "No route found between " << startStation << " and " << endStation << ".\n";
            }
        } else if (choice == 2) {
            auto result = metroMap.findShortestPathByTime(startStation, endStation);
            if (!result.path.empty()) {
                std::cout << "Route found:\n";
                for (const auto& station : result.path) {
                    std::cout << station << " -> ";
                }
                std::cout << "End\n";
                std::cout << "Total Time: " << result.time << " minutes\n";
            } else {
                std::cout << "No route found between " << startStation << " and " << endStation << ".\n";
            }
        } else {
            std::cout << "Invalid choice.\n";
        }
    }
};

#endif // USER_OPERATIONS_H
