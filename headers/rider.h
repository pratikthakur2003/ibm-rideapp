#ifndef RIDER_H
#define RIDER_H

#include <string>
#include "../models/User.h"
#include "../headers/userBase.h"

class rider : public UserBase
{
public:
    void addRiderToAvailable(const User &rider);
    void checkRiderStatus(const User &rider);
    int countRiderCompletedRides(int rider_id);

    void showUserProfile(const User &u) override
    {
        UserBase::showUserProfile(u);
    }
};

extern rider rd;

#endif
