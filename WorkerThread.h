#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>

class DashboardWorker : public QThread {
    Q_OBJECT

public:
    void run() override {
        // Aici faci interogari grele pe baza de date (ex: SUM, GROUP BY pt produse)
        // ... simulam un proces greu ...
        QThread::sleep(2);

        QString statsResult = "Vanzari: 15.000 RON | Cele mai vandute: Bormasina, Suruburi";

        // Trimitem rezultatul catre UI
        emit statsReady(statsResult);
    }

signals:
    void statsReady(const QString& stats);
};

#endif 