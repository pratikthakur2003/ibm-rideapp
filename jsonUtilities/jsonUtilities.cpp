#include "../headers/jsonUtilities.h"

using namespace std;

jsonUtilities j;
std::string availableRidersFile = "available_riders.json";

json jsonUtilities::loadJson(const string &filename)
{
    ifstream file(filename);
    json j;
    if (file.is_open())
        file >> j;
    return j;
}

void jsonUtilities::saveJson(const string &filename, const json &j)
{
    ofstream file(filename);
    file << j.dump(4);
}

void jsonUtilities::loadUsers(const string &filename)
{
    ifstream file(filename);
    json j;
    file >> j;
    for (auto &item : j)
    {
        User u;
        u.user_id = item["user_id"];
        u.full_name = item["full_name"];
        u.email = item["email"];
        u.phone = item["phone"];
        u.role = item["role"];
        u.created_at = item["created_at"];
        if (u.role == "rider")
            riders.push_back(u);
        else if (u.role == "driver")
            drivers.push_back(u);
    }
}

void jsonUtilities::loadVehicles(const string &filename)
{
    ifstream file(filename);
    json j;
    file >> j;
    for (auto &item : j)
    {
        Vehicle v;
        v.vehicle_id = item["vehicle_id"];
        v.driver_id = item["driver_id"];
        v.make = item["make"];
        v.model = item["model"];
        v.year = item["year"];
        v.registration_number = item["registration_number"];
        v.color = item["color"];
        vehicles.push_back(v);
    }
}

void jsonUtilities::loadRides(const string &filename)
{
    ifstream file(filename);
    json j;
    file >> j;
    for (auto &item : j)
    {
        Ride r;
        r.ride_id = item["ride_id"];
        r.rider_id = item["rider_id"];
        r.driver_id = item["driver_id"];
        r.vehicle_id = item["vehicle_id"];
        r.pickup_location = item["pickup_location"];
        r.drop_location = item["drop_location"];
        r.status = item["status"];
        r.fare = item["fare"];
        r.ride_date = item["ride_date"];
        r.ratings = item["ratings"];
        rides.push_back(r);
    }
}
