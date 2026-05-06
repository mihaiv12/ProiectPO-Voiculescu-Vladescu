#include "CartWindow.h"
#include <QHeaderView>
#include <QMessageBox>
#include <QTableWidgetItem>

CartWindow::CartWindow(QList<Product> cart, QWidget *parent)
    : QWidget(parent), m_cart(cart) {
    setupUI();
    loadCart();
}

void CartWindow::setupUI() {
    setWindowTitle("🛒 Coșul meu - Magazin Bricolaj");
    setMinimumSize(700, 500);
    setStyleSheet(R"(
        QWidget {
            background-color: #16213e;
        }
        QTableWidget {
            background-color: #0f3460;
            color: white;
            gridline-color: #e94560;
            font-size: 14px;
        }
        QHeaderView::section {
            background-color: #e94560;
            color: white;
            font-size: 14px;
            font-weight: bold;
            padding: 8px;
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
            font-size: 16px;
            font-weight: bold;
        }
    )");

    auto *mainLayout = new QVBoxLayout(this);

    QLabel *titleLabel = new QLabel("🛍️ Coșul de cumpărături");
    QFont titleFont;
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("color: #e94560; margin: 15px;");
    mainLayout->addWidget(titleLabel);

    m_cartTable = new QTableWidget();
    m_cartTable->setColumnCount(4);
    m_cartTable->setHorizontalHeaderLabels({"ID", "Produs", "Preț (RON)", ""});
    m_cartTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    m_cartTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    m_cartTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    m_cartTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);
    m_cartTable->setEditTriggers(QTableWidget::NoEditTriggers);
    m_cartTable->setAlternatingRowColors(true);
    mainLayout->addWidget(m_cartTable);

    auto *bottomLayout = new QHBoxLayout();

    m_totalLabel = new QLabel("Total: 0.00 RON");
    m_totalLabel->setStyleSheet("font-size: 18px; color: #4ecdc4;");

    bottomLayout->addWidget(m_totalLabel);
    bottomLayout->addStretch();

    m_removeButton = new QPushButton("🗑️ Șterge selectat");
    m_checkoutButton = new QPushButton("✅ Finalizare comandă");
    m_closeButton = new QPushButton("✖️ Închide");

    bottomLayout->addWidget(m_removeButton);
    bottomLayout->addWidget(m_checkoutButton);
    bottomLayout->addWidget(m_closeButton);

    mainLayout->addLayout(bottomLayout);

    connect(m_removeButton, &QPushButton::clicked, this, &CartWindow::removeSelected);
    connect(m_checkoutButton, &QPushButton::clicked, this, &CartWindow::checkout);
    connect(m_closeButton, &QPushButton::clicked, this, &CartWindow::close);
}

void CartWindow::loadCart() {
    m_cartTable->setRowCount(m_cart.size());
    double total = 0;

    for (int i = 0; i < m_cart.size(); ++i) {
        const Product& p = m_cart[i];
        m_cartTable->setItem(i, 0, new QTableWidgetItem(QString::number(p.getId())));
        m_cartTable->setItem(i, 1, new QTableWidgetItem(p.getName()));
        m_cartTable->setItem(i, 2, new QTableWidgetItem(QString::number(p.getPrice(), 'f', 2)));

        QPushButton *removeBtn = new QPushButton("❌ Șterge");
        removeBtn->setStyleSheet("background-color: #ff6b6b; padding: 5px;");
        m_cartTable->setCellWidget(i, 3, removeBtn);

        connect(removeBtn, &QPushButton::clicked, this, [this, i]() {
            m_cart.removeAt(i);
            loadCart();
            emit cartUpdated(m_cart);
        });

        total += p.getPrice();
    }

    m_totalLabel->setText("💰 Total: " + QString::number(total, 'f', 2) + " RON");
}

void CartWindow::removeSelected() {
    int currentRow = m_cartTable->currentRow();
    if (currentRow >= 0 && currentRow < m_cart.size()) {
        m_cart.removeAt(currentRow);
        loadCart();
        emit cartUpdated(m_cart);
        QMessageBox::information(this, "Șters", "Produsul a fost șters din coș!");
    } else {
        QMessageBox::warning(this, "Atenție", "Selectați un produs pentru a-l șterge!");
    }
}

void CartWindow::checkout() {
    if (m_cart.isEmpty()) {
        QMessageBox::warning(this, "Eroare", "Coșul este gol!");
        return;
    }

    QMessageBox::information(this, "Comandă", "Veți fi redirecționat către pagina de plată.");
}