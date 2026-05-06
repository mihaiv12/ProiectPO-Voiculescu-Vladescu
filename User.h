#ifndef USER_H
#define USER_H

#include <QString>

class User {
public:
    enum UserType { Regular, Loyal, Problematic };

    User(int id = -1, QString username = "", QString password = "",
         UserType type = Regular, int orderCount = 0);

    int getId() const;
    QString getUsername() const;
    QString getPassword() const;
    UserType getType() const;
    int getOrderCount() const;

    void setType(UserType type);
    void incrementOrderCount();

private:
    int m_id;
    QString m_username;
    QString m_password;
    UserType m_type;
    int m_orderCount;
};

#endif // USER_H