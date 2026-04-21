#include "Logger.h"
#include <QFile>
#include <QTextStream>
#include <QDateTime>
#include <QDebug>

void Logger::log(const QString& message) {
    QFile file("app_journal.log");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << " [INFO] " << message << "\n";
    }
    qDebug() << "[INFO]" << message;
}

void Logger::logError(const QString& errorMessage) {
    QFile file("app_journal.log");
    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << " [ERROR] " << errorMessage << "\n";
    }
    qWarning() << "[ERROR]" << errorMessage;
}