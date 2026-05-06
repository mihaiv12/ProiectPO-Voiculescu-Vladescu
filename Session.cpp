#include "Session.h"

Session& Session::getInstance() {
    static Session instance;
    return instance;
}

User Session::getCurrentUser() const { return m_currentUser; }

void Session::setCurrentUser(const User& user) {
    m_currentUser = user;
    m_loggedIn = true;
}

bool Session::isLoggedIn() const { return m_loggedIn; }

void Session::logout() { m_loggedIn = false; }