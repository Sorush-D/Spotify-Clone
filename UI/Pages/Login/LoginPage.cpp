#include "LoginPage.h"
#include <QHBoxLayout>

LoginPage::LoginPage(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
}


void LoginPage::setupUI() {
    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("Username");

    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Password");
    passwordEdit->setEchoMode(QLineEdit::Password);

    loginButton = new QPushButton("Login", this);
    signupButton = new QPushButton("Sign Up", this);

    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color:red;");
    errorLabel->hide();

    auto *layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(usernameEdit);
    layout->addWidget(passwordEdit);
    layout->addWidget(errorLabel);

    auto *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(loginButton);
    buttonsLayout->addWidget(signupButton);

    layout->addLayout(buttonsLayout);
    layout->addStretch();
}


void LoginPage::setupConnections() {
    connect(loginButton, &QPushButton::clicked, this, [this]() {
        clearError();

        emit loginRequested(
            usernameEdit->text().trimmed(),
            passwordEdit->text()
        );
    });

    connect(signupButton, &QPushButton::clicked, this, &LoginPage::signupRequested);
}


void LoginPage::clearFields() {
    usernameEdit->clear();
    passwordEdit->clear();

    clearError();
}


void LoginPage::setError(const QString &message) {
    errorLabel->setText(message);
    errorLabel->show();
}


void LoginPage::clearError() {
    errorLabel->clear();
    errorLabel->hide();
}

