#include "../headers/jsonUtilities.h"
#include "../headers/menu.h"

int main() {
    j.loadUsers("users.json");
    j.loadVehicles("vehicles.json");
    j.loadRides("rides.json");
    int choice;
    while (true) {
        std::cout << "\n=== Ride-Hailing App ===\n";
        std::cout << "1. Rider Menu\n";
        std::cout << "2. Driver Menu\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter choice: ";
        std::cin >> choice;
        if (choice == 1) m.riderMenu();
        else if (choice == 2) m.driverMenu();
        else if (choice == 0) break;
        else std::cout << "Invalid choice.\n";
    }
}
