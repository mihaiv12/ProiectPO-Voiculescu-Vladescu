#include "UserRepository.h"
#include "Logger.h"
#include <QSqlQuery>
#include <QVariant>

client UserRepository::getUserByEmail(const QString& email) {
    QSqlQuery query;
    query.prepare("SELECT id, email, passwordHash, isProblematic, completedOrdersCount FROM Users WHERE email = :email");
    query.bindValue(":email", email);

    if (query.exec() && query.next()) {
        client user(query.value(0).toInt(), query.value(1).toString(), query.value(2).toString(), query.value(3).toBool(), query.value(4).toInt());
        return user;
    }
    else {
        Logger::logError("Utilizatorul nu a fost gasit: " + email);
        return client(0, " ", " ", 0, 0);
    }
    
}

bool UserRepository::updateUserStatus(int userId, bool isProblematic) {
    QSqlQuery query;
    query.prepare("UPDATE Users SET isProblematic = :status WHERE id = :id");
    query.bindValue(":status", isProblematic ? 1 : 0);
    query.bindValue(":id", userId);
    return query.exec();
}