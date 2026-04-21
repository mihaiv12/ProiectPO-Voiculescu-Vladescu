#include "Services.h"
#include "Logger.h"

bool UserService::toggleCustomerProblematicStatus(account* actor, client* target) {
    admin* ADMIN = dynamic_cast<admin*>(actor);

    if (!ADMIN) {
        Logger::logError("Acces Refuzat: Doar administratorii pot marca utilizatori problematici.");
        return false;
    }

    if (!target) return false;

    target->toggleProb();
    
    QString status = target->returnProb() ? "PROBLEMATIC" : "OK";

    Logger::log("ADMIN ACTION: " + ADMIN->returnmail() + " a marcat pe " +
        target->returnmail() + " ca fiind " + status);
    return true;
}

double OrderService::calculateDiscount(client* customer, double cartTotal) {
    if (!customer) return cartTotal;

    double discountPercentage = 0.0;
    if (customer->returnOrder() >= 10) {
        discountPercentage = 0.10;
    }
    else if (customer->returnOrder() >= 5) {
        discountPercentage = 0.05;
    }

    return cartTotal - (cartTotal * discountPercentage);
}

bool OrderService::placeOrder(account* user, Order& order) {
    client* customer = dynamic_cast<client*>(user);
    if (customer->isAdmin() == 1) {
        Logger::logError("Eroare: Administratorii nu pot plasa comenzi.");
        return false;
    }

    if (customer->returnProb() == true && order.returnPay() == "Ramburs") {
        Logger::logError("Comanda respinsa: Clientul problematic " +
            customer->returnmail() + " trebuie sa plateasca Online.");
        return false;
    }
    if(customer->returnPortofel() - order.returnFinalPrice() < 0)
    {
        Logger::logError("Clientul nu are suficienti bani in cont. ");
        return false;
    }
    customer->incOrder();
    customer->decPortofel(order.returnFinalPrice());
    Logger::log("Comanda plasata cu succes pentru clientul: " + customer->returnmail());
    return true;
}