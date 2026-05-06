#include "AuthController.h"
#include <QMap>

static QMap<QString, User> mockUsers = {
    {"rares", User(1, "rares", "1234", User::Regular, 1)},
    {"mihai", User(2, "mihai", "1234", User::Loyal, 5)},
    {"problem", User(3, "problem", "1234", User::Problematic, 10)}
};

User AuthController::authenticate(const QString& username, const QString& password) {
    if (mockUsers.contains(username) && mockUsers[username].getPassword() == password) {
        return mockUsers[username];
    }
    return User();
}

bool AuthController::registerUser(const User& user) {
    if (mockUsers.contains(user.getUsername())) return false;
    mockUsers[user.getUsername()] = user;
    return true;
}