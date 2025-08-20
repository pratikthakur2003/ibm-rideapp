#ifndef RIDER_H
#define RIDER_H

#include <string>
#include "../models/User.h"


class rider {
    public:
    void showUserProfile(const User &u);
    void addRiderToAvailable(const User &rider);
    void checkRiderStatus(const User &rider);
    int countRiderCompletedRides(int rider_id);
};

extern rider rd;

#endif 
