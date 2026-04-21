#include "client.h"
client::client(int _id, QString _email, QString _hash, int _isProb, int _c) :
	account(_id, _email, _hash), isProblematic(_isProb), completedOrdersCount(_c)
{
}

bool client::isAdmin() const
{
	return false;
}

void client::incOrder()
{
	completedOrdersCount++;
}

void client::decPortofel(int value)
{
	portofel = portofel - value;
}

int client::returnOrder()
{
	return completedOrdersCount;
}

bool client::returnProb()
{
	return isProblematic;
}

void client::toggleProb()
{
	if (isProblematic == true)
		isProblematic = false;
	else
		isProblematic = true;
}

int client::returnPortofel()
{
	return portofel;
}