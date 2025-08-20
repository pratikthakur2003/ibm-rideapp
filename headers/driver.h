#ifndef DRIVER_H
#define DRIVER_H

#include "../models/User.h"
#include "../models/Vehicle.h"


class driver {
    public:
    void showUserProfile(const User &u);
    Vehicle* findVehicleByDriver(int driver_id);
    double calculateDriverEarnings(int driver_id);
    double calculateDriverAvgRating(int driver_id);
    void driverLookForRiders(const User &driver);
};

extern driver dr;

#endif 
