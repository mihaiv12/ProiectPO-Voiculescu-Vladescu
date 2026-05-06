#include "CatalogWindow.h"
#include "CartWindow.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QTableWidgetItem>

CatalogWindow::CatalogWindow(QWidget *parent) : QWidget(parent) {
    m_allProducts = getMockProducts();
    setupUI();
    loadProducts(m_allProducts);
}

void CatalogWindow::setupUI() {
    setWindowTitle("Catalog Produse - Magazin Bricolaj");
    resize(1200, 700);
    showMaximized();

    setStyleSheet(R"(
        QWidget {
            background-color: #16213e;
        }
        QTableWidget {
            background-color: #0f3460;
            color: white;
            gridline-color: #e94560;
            font-size: 14px;
            alternate-background-color: #1a1a2e;
        }
        QTableWidget::item {
            padding: 8px;
        }
        QHeaderView::section {
            background-color: #e94560;
            color: white;
            font-size: 14px;
            font-weight: bold;
            padding: 8px;
        }
        QComboBox, QLineEdit {
            background-color: #0f3460;
            color: white;
            border: 2px solid #e94560;
            border-radius: 8px;
            padding: 8px;
            font-size: 14px;
            min-width: 150px;
        }
        QPushButton {
            background-color: #e94560;
            color: white;
            border: none;
            border-radius: 8px;
            padding: 10px 20px;
            font-size: 14px;
            font-weight: bold;
        }
        QPushButton:hover {
            background-color: #c73e56;
        }
        QLabel {
            color: white;
            font-size: 14px;
            font-weight: bold;
        }
    )");

    auto *mainLayout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("Catalog Produse");
    QFont titleFont;
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: #e94560; margin: 20px;");
    mainLayout->addWidget(titleLabel);

    auto *filterLayout = new QHBoxLayout();
    filterLayout->setSpacing(15);

    filterLayout->addWidget(new QLabel("Categorie:"));
    m_categoryCombo = new QComboBox();
    m_categoryCombo->addItem("Toate");
    m_categoryCombo->addItem("Scule electrice");
    m_categoryCombo->addItem("Unelte manuale");
    m_categoryCombo->addItem("Ferramente");
    m_categoryCombo->addItem("Vopseluri");
    m_categoryCombo->addItem("Iluminat");
    filterLayout->addWidget(m_categoryCombo);

    filterLayout->addWidget(new QLabel("Pret min:"));
    m_minPriceEdit = new QLineEdit();
    m_minPriceEdit->setPlaceholderText("0");
    filterLayout->addWidget(m_minPriceEdit);

    filterLayout->addWidget(new QLabel("Pret max:"));
    m_maxPriceEdit = new QLineEdit();
    m_maxPriceEdit->setPlaceholderText("1000");
    filterLayout->addWidget(m_maxPriceEdit);

    m_filterButton = new QPushButton("Aplica filtre");
    filterLayout->addWidget(m_filterButton);

    filterLayout->addStretch();

    m_cartButton = new QPushButton("Cos (" + QString::number(m_cart.size()) + ")");
    m_cartButton->setStyleSheet("background-color: #4ecdc4; color: #1a1a2e;");
    filterLayout->addWidget(m_cartButton);

    mainLayout->addLayout(filterLayout);

    m_productTable = new QTableWidget();
    m_productTable->setColumnCount(5);
    m_productTable->setHorizontalHeaderLabels({"ID", "Produs", "Categorie", "Pret (RON)", "Actiune"});
    m_productTable->setEditTriggers(QTableWidget::NoEditTriggers);
    m_productTable->setAlternatingRowColors(true);
    m_productTable->setSelectionBehavior(QTableWidget::SelectRows);

    m_productTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    m_productTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_productTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    m_productTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    m_productTable->horizontalHeader()->setSectionResizeMode(4, QHeaderView::Fixed);
    m_productTable->setColumnWidth(4, 120);

    mainLayout->addWidget(m_productTable);

    connect(m_filterButton, &QPushButton::clicked, this, &CatalogWindow::filterProducts);
    connect(m_cartButton, &QPushButton::clicked, this, &CatalogWindow::viewCart);
}

void CatalogWindow::loadProducts(const QList<Product>& products) {
    m_productTable->setRowCount(products.size());

    for (int i = 0; i < products.size(); ++i) {
        const Product& p = products.at(i);

        m_productTable->setItem(i, 0, new QTableWidgetItem(QString::number(p.getId())));
        m_productTable->setItem(i, 1, new QTableWidgetItem(p.getName()));
        m_productTable->setItem(i, 2, new QTableWidgetItem(p.getCategory()));
        m_productTable->setItem(i, 3, new QTableWidgetItem(QString::number(p.getPrice(), 'f', 2)));

        QPushButton *addButton = new QPushButton("ADAUGA");
        addButton->setStyleSheet("background-color: #00ff88; color: black; padding: 8px; border-radius: 5px; font-weight: bold; font-size: 12px;");
        addButton->setCursor(Qt::PointingHandCursor);
        addButton->setFixedWidth(90);

        connect(addButton, &QPushButton::clicked, this, [this, p]() {
            addToCart(p);
        });

        m_productTable->setCellWidget(i, 4, addButton);
    }
}

void CatalogWindow::filterProducts() {
    QString category = m_categoryCombo->currentText();
    double minPrice = m_minPriceEdit->text().toDouble();
    double maxPrice = m_maxPriceEdit->text().isEmpty() ? 10000 : m_maxPriceEdit->text().toDouble();

    QList<Product> filtered;
    for (int i = 0; i < m_allProducts.size(); ++i) {
        const Product& p = m_allProducts.at(i);
        bool categoryMatch = (category == "Toate") || (p.getCategory() == category);
        bool priceMatch = (p.getPrice() >= minPrice && p.getPrice() <= maxPrice);

        if (categoryMatch && priceMatch) {
            filtered.append(p);
        }
    }
    loadProducts(filtered);
}

void CatalogWindow::addToCart(const Product& product) {
    m_cart.append(product);
    m_cartButton->setText("Cos (" + QString::number(m_cart.size()) + ")");
    QMessageBox::information(this, "Adaugat", product.getName() + " a fost adaugat in cos!");
}

void CatalogWindow::viewCart() {
    if (m_cart.isEmpty()) {
        QMessageBox::information(this, "Cos", "Cosul tau este gol!");
        return;
    }

    CartWindow *cartWindow = new CartWindow(m_cart, this);

    connect(cartWindow, &CartWindow::cartUpdated, this, [this](QList<Product> updatedCart) {
        m_cart = updatedCart;
        m_cartButton->setText("Cos (" + QString::number(m_cart.size()) + ")");
    });

    cartWindow->setAttribute(Qt::WA_DeleteOnClose);
    cartWindow->show();
}