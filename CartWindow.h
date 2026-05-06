#ifndef CARTWINDOW_H
#define CARTWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "Product.h"

class CartWindow : public QWidget {
    Q_OBJECT

public:
    explicit CartWindow(QList<Product> cart, QWidget *parent = nullptr);

signals:
    void cartUpdated(QList<Product> updatedCart);

private slots:
    void removeSelected();
    void checkout();

private:
    void loadCart();
    void setupUI();

    QTableWidget *m_cartTable;
    QPushButton *m_removeButton;
    QPushButton *m_checkoutButton;
    QPushButton *m_closeButton;
    QLabel *m_totalLabel;
    QList<Product> m_cart;
};

#endif // CARTWINDOW_H