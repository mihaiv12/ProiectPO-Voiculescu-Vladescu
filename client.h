#pragma once
#include "account.h"
class client : public account
{
private:
    bool isProblematic = false;
    int completedOrdersCount = 0;
    int portofel = 300;
public:
    client(int _id, QString _email, QString _hash, int _isProb, int _c);

    bool isAdmin() const override;
    void incOrder() override;

    void decPortofel(int value)override;

    int returnOrder()override;
    bool returnProb()override;

    void toggleProb()override;

    int returnPortofel()override;
};

