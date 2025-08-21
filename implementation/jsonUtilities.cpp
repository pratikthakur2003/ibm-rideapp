#include "../headers/jsonUtilities.h"

using namespace std;

jsonUtilities j;
std::string availableRidersFile = "files/available_riders.json";
std::string usersFile = "files/users.json";

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

int jsonUtilities::getNextUserId()
{
    json users = loadJson(usersFile);
    int maxId = 0;
    if (users.is_array())
    {
        for (auto &item : users)
        {
            int id = item.value("user_id", 0);
            if (id > maxId)
                maxId = id;
        }
    }
    return maxId + 1;
}

bool jsonUtilities::emailExists(const std::string &email)
{
    json users = loadJson(usersFile);
    if (users.is_array())
    {
        for (auto &item : users)
        {
            if (item.value("email", std::string()) == email)
                return true;
        }
    }
    return false;
}

User jsonUtilities::registerUser(const std::string &full_name, const std::string &email, const std::string &phone, const std::string &role)
{
    json users = loadJson(usersFile);
    if (!users.is_array())
        users = json::array();

    int newId = getNextUserId();

    json newUser = {
        {"user_id", newId},
        {"full_name", full_name},
        {"email", email},
        {"phone", phone},
        {"role", role}};

    users.push_back(newUser);
    saveJson(usersFile, users);

    User u;
    u.user_id = newId;
    u.full_name = full_name;
    u.email = email;
    u.phone = phone;
    u.role = role;
 
    if (role == "rider")
        riders.push_back(u);
    else if (role == "driver")
        drivers.push_back(u);

    return u;
}
