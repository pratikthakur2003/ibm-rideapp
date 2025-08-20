#ifndef MENU_H
#define MENU_H

#include "../models/User.h"


class menu {
    private:
    User* currentRider;
    User* currentDriver;
    
    public:
    menu();
    
    void riderMenu();
    void driverMenu();
};

extern menu m;

#endif
