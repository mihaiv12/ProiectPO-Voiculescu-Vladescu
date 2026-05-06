#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include <QString>
#include "User.h"

class AuthController {
public:
    static User authenticate(const QString& username, const QString& password);
    static bool registerUser(const User& user);
};

#endif // AUTHCONTROLLER_H