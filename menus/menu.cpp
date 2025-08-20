#include <iostream>
#include <iomanip>
#include "../headers/menu.h"
#include "../headers/rider.h"
#include "../headers/driver.h"
#include "../headers/jsonUtilities.h"

using namespace std;

// jsonUtilities j;
// rider rd;
// driver dr;
menu m;

menu::menu() {
    currentRider = nullptr;
    currentDriver = nullptr;
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
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            cout << "Enter Rider ID: ";
            cin >> id;
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
            if (!currentRider) {
                cout << "Please login first.\n";
                continue;
            }
            cout << "Completed Rides: "
                 << rd.countRiderCompletedRides(currentRider->user_id) << "\n";

        } else if (choice == 3) {
            if (!currentRider) {
                cout << "Please login first.\n";
                continue;
            }
            char ans;
            cout << "Looking for a ride? (Y/N): ";
            cin >> ans;
            if (ans == 'Y' || ans == 'y') {
                rd.addRiderToAvailable(*currentRider);
            }

        } else if (choice == 4) {
            if (!currentRider) {
                cout << "Please login first.\n";
                continue;
            }
            rd.checkRiderStatus(*currentRider);

        } else if (choice == 0) {
            return;
        } else {
            cout << "Invalid choice.\n";
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
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            int id;
            cout << "Enter Driver ID: ";
            cin >> id;
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
            if (!currentDriver) {
                cout << "Please login first.\n";
                continue;
            }
            cout << "Total Earnings: $"
                 << dr.calculateDriverEarnings(currentDriver->user_id) << "\n";

        } else if (choice == 3) {
            if (!currentDriver) {
                cout << "Please login first.\n";
                continue;
            }
            cout << "Average Rating: " << fixed << setprecision(2)
                 << dr.calculateDriverAvgRating(currentDriver->user_id) << "\n";

        } else if (choice == 4) {
            if (!currentDriver) {
                cout << "Please login first.\n";
                continue;
            }
            dr.driverLookForRiders(*currentDriver);

        } else if (choice == 0) {
            return;
        } else {
            cout << "Invalid choice.\n";
        }
    }
}
