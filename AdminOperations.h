// AdminOperations.h
#ifndef ADMIN_OPERATIONS_H
#define ADMIN_OPERATIONS_H

#include "MetroMap.h"
#include <iostream>
#include <string>

class AdminOperations {
public:
    static void addStation(MetroMap& metroMap) {
        std::string stationName;
        std::cout << "Enter the name of the station to add: ";
        std::cin.ignore();
        std::getline(std::cin, stationName);
        metroMap.addStation(stationName);
        std::cout << "Station '" << stationName << "' added successfully.\n";
    }

    static void removeStation(MetroMap& metroMap) {
        std::string stationName;
        std::cout << "Enter the name of the station to remove: ";
        std::cin.ignore();
        std::getline(std::cin, stationName);
        if (metroMap.removeStation(stationName)) {
            std::cout << "Station '" << stationName << "' removed successfully.\n";
        } else {
            std::cout << "Station '" << stationName << "' not found.\n";
        }
    }
};

#endif // ADMIN_OPERATIONS_H
