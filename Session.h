#ifndef SESSION_H
#define SESSION_H

#include "User.h"

class Session {
public:
    static Session& getInstance();

    User getCurrentUser() const;
    void setCurrentUser(const User& user);
    bool isLoggedIn() const;
    void logout();

private:
    Session() = default;
    User m_currentUser;
    bool m_loggedIn = false;
};

#endif // SESSION_H