#ifndef USERSERVICE_H
#define USERSERVICE_H
#include "Models.h"
#include "Logger.h"

class UserService {
public:
    // Doar un Admin poate schimba statusul unui client
    bool toggleProblematicStatus(Admin* admin, Customer* targetCustomer);
};

class OrderService {
public:
    // Verificam ca doar un Customer poate plasa comenzi
    bool canPlaceOrder(User* user);
};

#endif // USERSERVICE_H