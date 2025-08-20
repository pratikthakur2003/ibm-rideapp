#ifndef JSONUTILITIES_H
#define JSONUTILITIES_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "../external/json.hpp"
#include "../models/User.h"
#include "../models/Vehicle.h"
#include "../models/Ride.h"

using json = nlohmann::json;


class jsonUtilities
{
    public:
    std::vector<User> riders;
    std::vector<User> drivers;
    std::vector<Vehicle> vehicles;
    std::vector<Ride> rides;
    
    json loadJson(const std::string &filename);
    void saveJson(const std::string &filename, const json &j);
    void loadUsers(const std::string &filename);
    void loadVehicles(const std::string &filename);
    void loadRides(const std::string &filename);
};

extern jsonUtilities j;
extern std::string availableRidersFile;

#endif
