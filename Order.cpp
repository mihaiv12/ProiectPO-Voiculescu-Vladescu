#include "Order.h"

Order::Order(int _id, int _userId, QString _delivery, QString _payement, QString _status) :
	id(_id), userId(_userId), finalPrice(0), deliveryMethod(_delivery), paymentMethod(_payement), status(_status)
{

}

void Order::addProduct(Product* newProd)
{
	produse.push_back(newProd);
	finalPrice = finalPrice + newProd->returnPrice();
}

int Order::returnID()
{
	return id;
}

int Order::returnUser()
{
	return userId;
}

double Order::returnFinalPrice()
{
	return finalPrice;
}

QString Order::returnDel()
{
	return deliveryMethod;
}

QString Order::returnPay()
{
	return paymentMethod;
}

QString Order::returnSt()
{
	return status;
}

