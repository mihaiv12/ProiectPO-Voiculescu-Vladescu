#ifndef USERREPOSITORY_H
#define USERREPOSITORY_H

#include "client.h"
#include "admin.h"

class UserRepository {
public:
    client getUserByEmail(const QString& email);
    bool updateUserStatus(int userId, bool isProblematic);
};

#endif // USERREPOSITORY_H
