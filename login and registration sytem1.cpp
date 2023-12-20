#include <iostream>
#include <fstream>
#include <string>

class User {
public:
    std::string username;
    std::string password;

    User(const std::string& uname, const std::string& pwd)
        : username(uname), password(pwd) {}
};

class UserManager {
private:
    const std::string userFileName = "users.txt";
    std::fstream userFile;

public:
    UserManager() {
        userFile.open(userFileName, std::ios::app);  // Open file for appending
        if (!userFile.is_open()) {
            std::cerr << "Error: Unable to open user file." << std::endl;
        }
    }

    ~UserManager() {
        if (userFile.is_open()) {
            userFile.close();
        }
    }

    bool registerUser(const std::string& username, const std::string& password) {
        if (!userExists(username)) {
            userFile << username << " " << password << std::endl;
            std::cout << "Registration successful. User file created." << std::endl;
            return true;
        } else {
            std::cout << "Error: Username already exists. Please choose a different username." << std::endl;
            return false;
        }
    }

    bool loginUser(const std::string& username, const std::string& password) {
        std::string storedUsername, storedPassword;

        userFile.clear();  // Clear any flags that may interfere with file operations
        userFile.seekg(0, std::ios::beg);  // Move the file pointer to the beginning

        while (userFile >> storedUsername >> storedPassword) {
            if (storedUsername == username && storedPassword == password) {
                std::cout << "Login successful. Welcome, " << username << "!" << std::endl;
                return true;
            }
        }

        std::cout << "successfully login ." << std::endl;
        return false;
    }

private:
    bool userExists(const std::string& username) {
        std::string storedUsername;

        userFile.clear();  // Clear any flags that may interfere with file operations
        userFile.seekg(0, std::ios::beg);  // Move the file pointer to the beginning

        while (userFile >> storedUsername) {
            if (storedUsername == username) {
                return true;
            }
        }

        return false;
    }
};

int main() {
    UserManager userManager;

    int choice;
    std::string username, password;

    do {
        std::cout << "User Registration and Login System:" << std::endl;
        std::cout << "1. Register User" << std::endl;
        std::cout << "2. Login" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter a username: ";
                std::cin >> username;
                std::cout << "Enter a password: ";
                std::cin >> password;
                userManager.registerUser(username, password);
                break;
            case 2:
                std::cout << "Enter your username: ";
                std::cin >> username;
                std::cout << "Enter your password: ";
                std::cin >> password;
                userManager.loginUser(username, password);
                break;
            case 3:
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter a valid option." << std::endl;
        }

    } while (choice != 3);

    return 0;
}
