#ifndef USERBASE_H
#define USERBASE_H

#include <iostream>
#include "../models/User.h"
#include "../models/Vehicle.h"

class UserBase {
public:
    virtual void showUserProfile(const User &u) {
        std::cout << "\n--- User Profile ---\n";
        std::cout << "User ID: " << u.user_id << "\n";
        std::cout << "Full Name: " << u.full_name << "\n";
        std::cout << "Email: " << u.email << "\n";
        std::cout << "Phone: " << u.phone << "\n";
        std::cout << "Role: " << u.role << "\n";
        std::cout << "Account Created: " << u.created_at << "\n";
    }

    virtual ~UserBase() {}
};

#endif
