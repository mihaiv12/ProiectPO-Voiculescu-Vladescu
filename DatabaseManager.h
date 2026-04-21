#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QSqlDatabase>

class DatabaseManager {
public:
    static DatabaseManager& instance(); // Singleton simplu
    bool connect();
    void createTablesIfNotExist();

private:
    DatabaseManager() {}
    QSqlDatabase db;
};

#endif // DATABASEMANAGER_H