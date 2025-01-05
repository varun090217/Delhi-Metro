// UserAuth.h
#ifndef USER_AUTH_H
#define USER_AUTH_H

#include <iostream>
#include <unordered_map>
#include <string>

class UserAuth {
private:
    static std::unordered_map<std::string, std::string> adminCredentials; // Stores admin username-password pairs

public:
    // Initialize default admin credentials
    static void initialize() {
        adminCredentials["admin"] = "password123"; // Default admin account
    }

    // Authenticate admin
    static bool authenticate() {
        std::string username, password;
        std::cout << "Enter username: ";
        std::cin >> username;
        std::cout << "Enter password: ";
        std::cin >> password;

        if (adminCredentials.find(username) != adminCredentials.end() && adminCredentials[username] == password) {
            return true;
        }
        std::cout << "Invalid username or password.\n";
        return false;
    }

    // Create a new admin account
    static void createAdmin() {
        std::string username, password;
        std::cout << "Enter new username: ";
        std::cin >> username;

        if (adminCredentials.find(username) != adminCredentials.end()) {
            std::cout << "Username already exists.\n";
            return;
        }

        std::cout << "Enter new password: ";
        std::cin >> password;
        adminCredentials[username] = password;
        std::cout << "Admin account created successfully.\n";
    }
};

// Define the static member
std::unordered_map<std::string, std::string> UserAuth::adminCredentials;

#endif // USER_AUTH_H
