#pragma once
#include "account.h"
class admin : public account
{
private:
    int accessLevel = 1;
public:
    admin(int _id, QString _email, QString _hash, int _isProb, int _c);
    bool isAdmin() const override;
};

