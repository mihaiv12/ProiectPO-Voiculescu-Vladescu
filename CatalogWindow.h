#ifndef CATALOGWINDOW_H
#define CATALOGWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include "Product.h"

class CatalogWindow : public QWidget {
    Q_OBJECT

public:
    explicit CatalogWindow(QWidget *parent = nullptr);

private slots:
    void filterProducts();
    void addToCart(const Product& product);
    void viewCart();

private:
    void loadProducts(const QList<Product>& products);
    void setupUI();

    QTableWidget *m_productTable;
    QComboBox *m_categoryCombo;
    QLineEdit *m_minPriceEdit;
    QLineEdit *m_maxPriceEdit;
    QPushButton *m_filterButton;
    QPushButton *m_cartButton;
    QList<Product> m_allProducts;
    QList<Product> m_cart;
};

#endif // CATALOGWINDOW_H