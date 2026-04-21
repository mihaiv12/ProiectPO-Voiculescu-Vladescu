#include "DatabaseManager.h"
#include "Logger.h"
#include <QSqlQuery>
#include <QSqlError>

DatabaseManager& DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}

bool DatabaseManager::connect() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("sivg_mb.db");

    if (!db.open()) {
        Logger::logError("Nu s-a putut conecta la baza de date: " + db.lastError().text());
        return false;
    }
    Logger::log("Conexiune la baza de date stabilita.");
    return true;
}

void DatabaseManager::createTablesIfNotExist() {
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS Users (id INTEGER PRIMARY KEY AUTOINCREMENT, email TEXT, passwordHash TEXT, isProblematic INTEGER, completedOrdersCount INTEGER)");

}