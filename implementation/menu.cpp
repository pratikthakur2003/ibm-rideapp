#include <iostream>
#include <iomanip>
#include <limits>
#include "../headers/menu.h"
#include "../headers/rider.h"
#include "../headers/driver.h"
#include "../headers/jsonUtilities.h"

using namespace std;

menu m;

menu::menu() {
    currentRider = nullptr;
    currentDriver = nullptr;
}

int safeInputInt(const string &prompt) {
    int value;
    while (true) {
        try {
            cout << prompt;
            if (!(cin >> value)) {
                throw runtime_error("Invalid input. Please enter a number.");
            }
            return value;
        } catch (const exception &e) {
            cout << e.what() << "\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

char safeInputChar(const string &prompt) {
    char c;
    while (true) {
        try {
            cout << prompt;
            if (!(cin >> c)) {
                throw runtime_error("Invalid input. Please enter Y or N.");
            }
            if (c == 'Y' || c == 'y' || c == 'N' || c == 'n') {
                return c;
            } else {
                throw runtime_error("Invalid choice. Enter only Y or N.");
            }
        } catch (const exception &e) {
            cout << e.what() << "\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void menu::riderMenu() {
    int choice;
    while (true) {
        cout << "\n--- Rider Menu ---\n";
        cout << "1. Fetch Rider Data (Login)\n";
        cout << "2. Show No. of Completed Rides\n";
        cout << "3. Looking for a Ride? (Y/N)\n";
        cout << "4. Check Ride Request Status\n";
        cout << "0. Back\n";
        choice = safeInputInt("Enter choice: ");

        try {
            if (choice == 1) {
                int id = safeInputInt("Enter Rider ID: ");
                currentRider = nullptr;

                for (auto &r : j.riders) {
                    if (r.user_id == id) {
                        currentRider = &r;
                        cout << "\nLogin successful!\n";
                        rd.showUserProfile(*currentRider);
                        break;
                    }
                }
                if (!currentRider)
                    cout << "Rider not found!\n";

            } else if (choice == 2) {
                if (!currentRider) throw runtime_error("Please login first.");
                cout << "Completed Rides: "
                     << rd.countRiderCompletedRides(currentRider->user_id) << "\n";

            } else if (choice == 3) {
                if (!currentRider) throw runtime_error("Please login first.");
                char ans = safeInputChar("Looking for a ride? (Y/N): ");
                if (ans == 'Y' || ans == 'y') {
                    rd.addRiderToAvailable(*currentRider);
                }

            } else if (choice == 4) {
                if (!currentRider) throw runtime_error("Please login first.");
                rd.checkRiderStatus(*currentRider);

            } else if (choice == 0) {
                return;
            } else {
                cout << "Invalid choice.\n";
            }
        } catch (const exception &e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
}

void menu::driverMenu() {
    int choice;
    while (true) {
        cout << "\n--- Driver Menu ---\n";
        cout << "1. Fetch Driver Profile (Login)\n";
        cout << "2. Show Total Earnings\n";
        cout << "3. Show Average Rating\n";
        cout << "4. Look for Nearby Riders\n";
        cout << "0. Back\n";
        choice = safeInputInt("Enter choice: ");

        try {
            if (choice == 1) {
                int id = safeInputInt("Enter Driver ID: ");
                currentDriver = nullptr;

                for (auto &d : j.drivers) {
                    if (d.user_id == id) {
                        currentDriver = &d;
                        cout << "\nLogin successful!\n";
                        dr.showUserProfile(*currentDriver);
                        break;
                    }
                }
                if (!currentDriver)
                    cout << "Driver not found!\n";

            } else if (choice == 2) {
                if (!currentDriver) throw runtime_error("Please login first.");
                cout << "Total Earnings: $"
                     << dr.calculateDriverEarnings(currentDriver->user_id) << "\n";

            } else if (choice == 3) {
                if (!currentDriver) throw runtime_error("Please login first.");
                cout << "Average Rating: " << fixed << setprecision(2)
                     << dr.calculateDriverAvgRating(currentDriver->user_id) << "\n";

            } else if (choice == 4) {
                if (!currentDriver) throw runtime_error("Please login first.");
                dr.driverLookForRiders(*currentDriver);

            } else if (choice == 0) {
                return;
            } else {
                cout << "Invalid choice.\n";
            }
        } catch (const exception &e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
}
