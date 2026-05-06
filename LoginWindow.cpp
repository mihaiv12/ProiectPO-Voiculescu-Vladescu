#include "LoginWindow.h"
#include "AuthController.h"
#include "Session.h"
#include <QMessageBox>
#include <QFont>

LoginWindow::LoginWindow(QWidget *parent) : QWidget(parent) {
    // Setează fereastra pe ecran complet
    showFullScreen();

    setStyleSheet(R"(
        QWidget {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:1,
                                        stop:0 #1a1a2e, stop:1 #16213e);
        }
        QLabel {
            color: white;
            font-size: 14px;
        }
        QLineEdit {
            background-color: #0f3460;
            color: white;
            border: 2px solid #e94560;
            border-radius: 10px;
            padding: 12px;
            font-size: 14px;
            min-width: 300px;
        }
        QLineEdit:focus {
            border: 2px solid #f5a623;
        }
        QPushButton {
            background-color: #e94560;
            color: white;
            border: none;
            border-radius: 10px;
            padding: 12px;
            font-size: 16px;
            font-weight: bold;
            min-width: 200px;
        }
        QPushButton:hover {
            background-color: #c73e56;
        }
        QPushButton:pressed {
            background-color: #a32e45;
        }
    )");

    // Layout principal centrat
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setAlignment(Qt::AlignCenter);

    // Titlu mare "Bine ai venit!"
    QLabel *welcomeLabel = new QLabel("🏠 Bine ai venit la Magazinul Bricolaj!");
    QFont titleFont;
    titleFont.setPointSize(28);
    titleFont.setBold(true);
    welcomeLabel->setFont(titleFont);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    welcomeLabel->setStyleSheet("color: #e94560; margin-bottom: 30px;");

    // Subtitlu
    QLabel *subtitleLabel = new QLabel("Autentifică-te pentru a continua");
    QFont subFont;
    subFont.setPointSize(14);
    subtitleLabel->setFont(subFont);
    subtitleLabel->setAlignment(Qt::AlignCenter);
    subtitleLabel->setStyleSheet("color: #cccccc; margin-bottom: 40px;");

    // Frame pentru formular (ca un card)
    QFrame *formFrame = new QFrame();
    formFrame->setStyleSheet(R"(
        QFrame {
            background-color: rgba(30, 30, 60, 0.7);
            border-radius: 20px;
            padding: 30px;
        }
    )");
    auto *formLayout = new QVBoxLayout(formFrame);
    formLayout->setSpacing(15);

    // Label Username
    QLabel *userLabel = new QLabel("👤 Nume utilizator");
    userLabel->setStyleSheet("font-size: 14px; font-weight: bold; margin-top: 10px;");

    m_usernameEdit = new QLineEdit();
    m_usernameEdit->setPlaceholderText("Introdu username-ul...");
    m_usernameEdit->setMinimumWidth(350);

    // Label Password
    QLabel *passLabel = new QLabel("🔒 Parolă");
    passLabel->setStyleSheet("font-size: 14px; font-weight: bold; margin-top: 10px;");

    m_passwordEdit = new QLineEdit();
    m_passwordEdit->setPlaceholderText("Introdu parola...");
    m_passwordEdit->setEchoMode(QLineEdit::Password);

    // Buton Login
    m_loginButton = new QPushButton("🔓 LOG IN");
    m_loginButton->setCursor(Qt::PointingHandCursor);
    m_loginButton->setMinimumHeight(50);

    // Status label
    m_statusLabel = new QLabel();
    m_statusLabel->setAlignment(Qt::AlignCenter);
    m_statusLabel->setStyleSheet("color: #ff6b6b; margin-top: 15px;");

    // Adaugă toate în formLayout
    formLayout->addWidget(userLabel);
    formLayout->addWidget(m_usernameEdit);
    formLayout->addWidget(passLabel);
    formLayout->addWidget(m_passwordEdit);
    formLayout->addWidget(m_loginButton);
    formLayout->addWidget(m_statusLabel);

    // Adaugă în layout-ul principal
    mainLayout->addWidget(welcomeLabel);
    mainLayout->addWidget(subtitleLabel);
    mainLayout->addWidget(formFrame, 0, Qt::AlignCenter);

    // Conectare semnal
    connect(m_loginButton, &QPushButton::clicked, this, &LoginWindow::onLoginClicked);
}

void LoginWindow::onLoginClicked() {
    QString username = m_usernameEdit->text();
    QString password = m_passwordEdit->text();

    User user = AuthController::authenticate(username, password);

    if (user.getId() != -1) {
        Session::getInstance().setCurrentUser(user);
        m_statusLabel->setText("✅ Autentificare cu succes!");
        m_statusLabel->setStyleSheet("color: #4ecdc4; margin-top: 15px;");
        QMessageBox::information(this, "Succes", "Autentificare cu succes!\nBine ai venit, " + username + "!");
        emit loginSuccessful();
    } else {
        m_statusLabel->setText("❌ Autentificare eșuată! Verificați datele.");
        m_statusLabel->setStyleSheet("color: #ff6b6b; margin-top: 15px;");
        QMessageBox::warning(this, "Eroare", "Autentificare eșuată!\nUsername sau parolă incorecte.");
    }
}