#ifndef DRIVER_H
#define DRIVER_H

#include "../models/User.h"
#include "../models/Vehicle.h"
#include "../headers/userBase.h"

class driver : public UserBase
{
public:
    Vehicle *findVehicleByDriver(int driver_id);
    double calculateDriverEarnings(int driver_id);
    double calculateDriverAvgRating(int driver_id);
    void driverLookForRiders(const User &driver);

    void showUserProfile(const User &u) override
    {
        UserBase::showUserProfile(u);
        if (u.role == "driver")
        {
            Vehicle *v = findVehicleByDriver(u.user_id);
            if (v)
            {
                cout << "\n--- Vehicle Info ---\n";
                cout << "Make: " << v->make << "\n";
                cout << "Model: " << v->model << "\n";
                cout << "Year: " << v->year << "\n";
                cout << "Registration: " << v->registration_number << "\n";
                cout << "Color: " << v->color << "\n";
            }
        }
    }
};

extern driver dr;

#endif
