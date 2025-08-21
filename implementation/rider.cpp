#include <iostream>
#include "../external/json.hpp"
#include "../models/Vehicle.h"
#include "../models/Ride.h"
#include "../headers/rider.h"
#include "../headers/jsonUtilities.h"
#include "../headers/driver.h"

using namespace std;
rider rd;

void rider::addRiderToAvailable(const User &rider) {
    json available = j.loadJson(availableRidersFile);
    if (!available.is_array())
        available = json::array();

    for (auto &r : available) {
        if (r["user_id"] == rider.user_id && r["status"] == "Pending") {
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
