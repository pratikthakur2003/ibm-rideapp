#ifndef USER_H
#define USER_H

#include <string>

struct User {
    int user_id;
    std::string full_name;
    std::string email;
    std::string phone;
    std::string role;
    std::string created_at;
};

#endif
