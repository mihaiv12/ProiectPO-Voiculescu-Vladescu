#ifndef SERVICES_H
#define SERVICES_H

#include "client.h"
#include "admin.h"
#include "Order.h"

class UserService {
public:
    bool toggleCustomerProblematicStatus(account* actor, client* target);
};

class OrderService {
public:
    OrderService() {}

    double calculateDiscount(client* customer, double cartTotal);

    bool placeOrder(account* user, Order& order);
};

#endif 