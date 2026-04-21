#include "admin.h"
admin::admin(int _id, QString _email, QString _hash, int _isProb, int _c) :
	account(_id, _email, _hash)
{

}
bool admin::isAdmin() const
{
	return true;
}