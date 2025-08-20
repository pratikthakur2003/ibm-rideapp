#include "../headers/driver.h"
#include <iostream>
#include "../json.hpp"
#include "../models/Ride.h"
#include "../headers/jsonUtilities.h"

using namespace std;

// jsonUtilities j;
// string availableRidersFile = "available_riders.json";
driver dr;

void driver::showUserProfile(const User &u) {
    cout << "\n--- User Profile ---\n";
    cout << "User ID: " << u.user_id << "\n";
    cout << "Full Name: " << u.full_name << "\n";
    cout << "Email: " << u.email << "\n";
    cout << "Phone: " << u.phone << "\n";
    cout << "Role: " << u.role << "\n";
    cout << "Account Created: " << u.created_at << "\n";

    if (u.role == "driver") {
        Vehicle *v = findVehicleByDriver(u.user_id);
        if (v) {
            cout << "\n--- Vehicle Info ---\n";
            cout << "Make: " << v->make << "\n";
            cout << "Model: " << v->model << "\n";
            cout << "Year: " << v->year << "\n";
            cout << "Registration: " << v->registration_number << "\n";
            cout << "Color: " << v->color << "\n";
        }
    }
}

Vehicle* driver::findVehicleByDriver(int driver_id) {
    for (auto &v : j.vehicles) {
        if (v.driver_id == driver_id)
            return &v;
    }
    return nullptr;
}

double driver::calculateDriverEarnings(int driver_id) {
    double total = 0;
    for (auto &r : j.rides) {
        if (r.driver_id == driver_id && r.status == "completed") {
            total += r.fare;
        }
    }
    return total;
}

double driver::calculateDriverAvgRating(int driver_id) {
    double sum = 0;
    int count = 0;
    for (auto &r : j.rides) {
        for (auto &rating : r.ratings) {
            if (rating["given_to"] == driver_id) {
                sum += double(rating["score"]);
                count++;
            }
        }
    }
    return (count > 0) ? (sum / count) : 0.0;
}

void driver::driverLookForRiders(const User &driver) {
    json available = j.loadJson(availableRidersFile);
    if (!available.is_array() || available.empty()) {
        cout << "No riders currently looking for a ride.\n";
        return;
    }

    cout << "\nAvailable Riders:\n";
    for (size_t i = 0; i < available.size(); ++i) {
        cout << i + 1 << ". " << available[i]["full_name"]
             << " (Status: " << available[i]["status"] << ")\n";
    }

    int choice;
    cout << "Select a rider number to respond (0 to cancel): ";
    cin >> choice;
    if (choice <= 0 || choice > (int)available.size())
        return;

    cout << "Accept this ride? (Y/N): ";
    char ans;
    cin >> ans;
    if (ans == 'Y' || ans == 'y') {
        available[choice - 1]["status"] = "Accepted";
        available[choice - 1]["assigned_driver"] = driver.full_name;
        cout << "Ride accepted. Rider will be notified.\n";
    } else {
        cout << "Ride rejected.\n";
    }

    j.saveJson(availableRidersFile, available);
}
