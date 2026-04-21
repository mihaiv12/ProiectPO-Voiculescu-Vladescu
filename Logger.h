#ifndef LOGGER_H
#define LOGGER_H

#include <QString>

// CNF-04: Jurnalizare
class Logger {
public:
    static void log(const QString& message);
    static void logError(const QString& errorMessage);
};

#endif // LOGGER_H
