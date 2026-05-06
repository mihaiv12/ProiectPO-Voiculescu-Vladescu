#include "User.h"

User::User(int id, QString username, QString password, UserType type, int orderCount)
    : m_id(id), m_username(username), m_password(password), m_type(type), m_orderCount(orderCount) {}

int User::getId() const { return m_id; }
QString User::getUsername() const { return m_username; }
QString User::getPassword() const { return m_password; }
User::UserType User::getType() const { return m_type; }
int User::getOrderCount() const { return m_orderCount; }

void User::setType(UserType type) { m_type = type; }
void User::incrementOrderCount() { m_orderCount++; }