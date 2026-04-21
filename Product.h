#pragma once

#include <QString>
#include <QList>

class Product
{
private:
    int id = 0;
    QString name;
    double price = 0.0;
    bool isService = false; // CF-02: Pentru servicii de montaj
public:
    Product(int _id, QString _name, double _price, bool _isService);
    double returnPrice();
    bool returnService();
};

