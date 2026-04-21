#pragma once
#include <QString>
#include <QList>

class account {
protected:
    int id = 0;
    QString email;
    QString passwordHash;
public:
    account(int _id, QString _email, QString _hash)
        : id(_id), email(_email), passwordHash(_hash) {
    }
    virtual ~account() {}
    virtual bool isAdmin() const = 0;

    virtual int returnID() { return id; }
    virtual QString returnmail() { return email; }

    virtual void incOrder() {}

    virtual void decPortofel(int value) {}

    virtual int returnOrder() { return 0; }
    virtual bool returnProb() { return false; }

    virtual int returnPortofel() { return 0; }

    virtual void toggleProb() {}
};

