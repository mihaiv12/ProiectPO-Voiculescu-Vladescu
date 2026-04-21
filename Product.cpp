#include "Product.h"

Product::Product(int _id, QString _name, double _price, bool _isService) : id(_id), name(_name), price(_price), isService(_isService)
{
}

double Product::returnPrice()
{
	return price;
}

bool Product::returnService()
{
	return isService;
}

