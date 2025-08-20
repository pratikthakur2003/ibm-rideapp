#include <iostream>
#include <iomanip>
#include "../json.hpp"
#include "../models/Vehicle.h"
#include "../models/Ride.h"
#include "../headers/rider.h"
#include "../headers/jsonUtilities.h"
#include "../headers/driver.h"

using namespace std;

// jsonUtilities j;
rider rd;

// string availableRidersFile = "available_riders.json";

void rider::showUserProfile(const User &u) {
    cout << "\n--- User Profile ---\n";
    cout << "User ID: " << u.user_id << "\n";
    cout << "Full Name: " << u.full_name << "\n";
    cout << "Email: " << u.email << "\n";
    cout << "Phone: " << u.phone << "\n";
    cout << "Role: " << u.role << "\n";
    cout << "Account Created: " << u.created_at << "\n";

    if (u.role == "driver") {
        Vehicle *v = dr.findVehicleByDriver(u.user_id);
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

void rider::addRiderToAvailable(const User &rider) {
    json available = j.loadJson(availableRidersFile);
    if (!available.is_array())
        available = json::array();

    for (auto &r : available) {
        if (r["user_id"] == rider.user_id) {
            cout << "You are already waiting for a ride.\n";
            return;
        }
    }

    json riderData = {
        {"user_id", rider.user_id},
        {"full_name", rider.full_name},
        {"status", "Pending"},
        {"assigned_driver", nullptr}
    };

    available.push_back(riderData);
    j.saveJson(availableRidersFile, available);
    cout << "You are now waiting for a driver...\n";
}

void rider::checkRiderStatus(const User &rider) {
    json available = j.loadJson(availableRidersFile);
    for (auto &r : available) {
        if (r["user_id"] == rider.user_id) {
            cout << "Your ride status: " << r["status"];
            if (!r["assigned_driver"].is_null())
                cout << " (" << r["assigned_driver"] << ")";
            cout << "\n";
            return;
        }
    }
    cout << "No active ride request found.\n";
}

int rider::countRiderCompletedRides(int rider_id) {
    int count = 0;
    for (auto &r : j.rides) {
        if (r.rider_id == rider_id && r.status == "completed")
            count++;
    }
    return count;
}
