#ifndef RIDE_H
#define RIDE_H

#include <string>
#include <vector>
#include "../external/json.hpp"
using json = nlohmann::json;

struct Ride {
    int ride_id;
    int rider_id;
    int driver_id;
    int vehicle_id;
    std::string pickup_location;
    std::string drop_location;
    std::string status;
    double fare;
    std::string ride_date;
    std::vector<json> ratings;
};

#endif