#pragma once
#include <iostream>
using namespace std;

#include "Product.h"
#include <vector>

class Order
{
private:
    int id;
    int userId;
    double finalPrice;

    vector<Product*>produse;

    QString deliveryMethod; // "Curier" sau "Ridicare"
    QString paymentMethod;  // "Online" sau "Ramburs"
    QString status;         // "Noua", "Procesare", "Finalizata"
public:
    Order(int _id, int _userId, QString _delivery, QString _payement, QString _status);

    void addProduct(Product* newProd);

    int returnID();
    int returnUser();
    double returnFinalPrice();

    QString returnDel();
    QString returnPay();
    QString returnSt();

};
