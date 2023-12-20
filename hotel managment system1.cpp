#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm> // For std::remove_if
#include <iomanip>

class Customer {
public:
    std::string name;
    int roomNumber;
    double bill;

    Customer(const std::string& customerName, int roomNum, double initialBill = 0.0)
        : name(customerName), roomNumber(roomNum), bill(initialBill) {}

    // Function to display customer information
    void display() const {
        std::cout << "Customer Name: " << name << ", Room Number: " << roomNumber
                  << ", Bill: $" << std::fixed << std::setprecision(2) << bill << std::endl;
    }
};

class HotelManagementSystem {
private:
    std::vector<Customer> customers;
    const std::string dataFileName = "customer_data.txt";

public:
    void loadCustomerData() {
        std::ifstream dataFile(dataFileName);

        if (dataFile.is_open()) {
            std::string name;
            int roomNumber;
            double bill;

            while (dataFile >> name >> roomNumber >> bill) {
                customers.push_back(Customer(name, roomNumber, bill));
            }

            dataFile.close();
        } else {
            std::cerr << "Error: Unable to open data file." << std::endl;
        }
    }

    void saveCustomerData() {
        std::ofstream dataFile(dataFileName);

        if (dataFile.is_open()) {
            for (const auto& customer : customers) {
                dataFile << customer.name << " " << customer.roomNumber << " " << customer.bill << std::endl;
            }

            dataFile.close();
        } else {
            std::cerr << "Error: Unable to open data file for writing." << std::endl;
        }
    }

    void bookRoom(const std::string& name, int roomNumber) {
        customers.push_back(Customer(name, roomNumber));
        std::cout << "Room booked successfully." << std::endl;
    }

    void searchCustomer(const std::string& name) {
        auto it = std::find_if(customers.begin(), customers.end(), [&name](const Customer& customer) {
            return customer.name == name;
        });

        if (it != customers.end()) {
            it->display();
        } else {
            std::cout << "Customer not found." << std::endl;
        }
    }

    void viewTotalAllottedRooms() const {
        std::cout << "Total Allotted Rooms: " << customers.size() << std::endl;
    }

    void modifyCustomerRecord(const std::string& name, int newRoomNumber) {
        auto it = std::find_if(customers.begin(), customers.end(), [&name](const Customer& customer) {
            return customer.name == name;
        });

        if (it != customers.end()) {
            it->roomNumber = newRoomNumber;
            std::cout << "Record modified successfully." << std::endl;
        } else {
            std::cout << "Customer not found." << std::endl;
        }
    }

    void deleteCustomerRecord(const std::string& name) {
        auto it = std::remove_if(customers.begin(), customers.end(), [&name](const Customer& customer) {
            return customer.name == name;
        });

        if (it != customers.end()) {
            customers.erase(it, customers.end());
            std::cout << "Record deleted successfully." << std::endl;
        } else {
            std::cout << "Customer not found." << std::endl;
        }
    }

    void displayTotalBill(const std::string& name) const {
        auto it = std::find_if(customers.begin(), customers.end(), [&name](const Customer& customer) {
            return customer.name == name;
        });

        if (it != customers.end()) {
            std::cout << "Total Bill for " << it->name << ": $" << std::fixed << std::setprecision(2)
                      << it->bill << std::endl;
        } else {
            std::cout << "Customer not found." << std::endl;
        }
    }
};

int main() {
    HotelManagementSystem hotelSystem;
    hotelSystem.loadCustomerData();

    int choice;
    std::string name;
    int roomNumber;

    do {
        std::cout << "Hotel Management System Menu:" << std::endl;
        std::cout << "1. Book a room" << std::endl;
        std::cout << "2. Search for customer details" << std::endl;
        std::cout << "3. View total allotted rooms" << std::endl;
        std::cout << "4. Modify customer record" << std::endl;
        std::cout << "5. Delete customer record" << std::endl;
        std::cout << "6. Display total bill" << std::endl;
        std::cout << "7. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1:
                std::cout << "Enter customer name: ";
                std::cin >> name;
                std::cout << "Enter room number: ";
                std::cin >> roomNumber;
                hotelSystem.bookRoom(name, roomNumber);
                break;
            case 2:
                std::cout << "Enter customer name to search: ";
                std::cin >> name;
                hotelSystem.searchCustomer(name);
                break;
            case 3:
                hotelSystem.viewTotalAllottedRooms();
                break;
            case 4:
                std::cout << "Enter customer name to modify: ";
                std::cin >> name;
                std::cout << "Enter new room number: ";
                std::cin >> roomNumber;
                hotelSystem.modifyCustomerRecord(name, roomNumber);
                break;
            case 5:
                std::cout << "Enter customer name to delete: ";
                std::cin >> name;
                hotelSystem.deleteCustomerRecord(name);
                break;
            case 6:
                std::cout << "Enter customer name to display total bill: ";
                std::cin >> name;
                hotelSystem.displayTotalBill(name);
                break;
            case 7:
                hotelSystem.saveCustomerData();
                std::cout << "Exiting the program." << std::endl;
                break;
            default:
                std::cout << "Invalid choice. Please enter a valid option." << std::endl;
        }

    } while (choice != 7);

    return 0;
}
