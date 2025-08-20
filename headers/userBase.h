#ifndef USERBASE_H
#define USERBASE_H

#include <iostream>
#include "../models/User.h"
#include "../models/Vehicle.h"

using namespace std;

class UserBase {
public:
    virtual void showUserProfile(const User &u) {
        cout << "\n--- User Profile ---\n";
        cout << "User ID: " << u.user_id << "\n";
        cout << "Full Name: " << u.full_name << "\n";
        cout << "Email: " << u.email << "\n";
        cout << "Phone: " << u.phone << "\n";
        cout << "Role: " << u.role << "\n";
        cout << "Account Created: " << u.created_at << "\n";
    }

    virtual ~UserBase() {}
};

#endif
