#ifndef VEHICLE_H
#define VEHICLE_H

#include <string>

struct Vehicle {
    int vehicle_id;
    int driver_id;
    std::string make;
    std::string model;
    int year;
    std::string registration_number;
    std::string color;
};

#endif // VEHICLE_H
