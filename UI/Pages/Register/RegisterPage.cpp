#include "RegisterPage.h"
#include <QVBoxLayout>

RegisterPage::RegisterPage(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
}


void RegisterPage::setupUI() {
    fullNameEdit = new QLineEdit(this);
    fullNameEdit->setPlaceholderText("Full name");

    usernameEdit = new QLineEdit(this);
    usernameEdit->setPlaceholderText("Username");

    passwordEdit = new QLineEdit(this);
    passwordEdit->setPlaceholderText("Password");
    passwordEdit->setEchoMode(QLineEdit::Password);

    confirmPasswordEdit = new QLineEdit(this);
    confirmPasswordEdit->setPlaceholderText("Confirm password");
    confirmPasswordEdit->setEchoMode(QLineEdit::Password);

    listenerRadio = new QRadioButton("Listener", this);
    artistRadio = new QRadioButton("Artist", this);
    listenerRadio->setChecked(true);

    signupButton = new QPushButton("Sign Up", this);
    loginButton = new QPushButton("Login", this);

    errorLabel = new QLabel(this);
    errorLabel->setStyleSheet("color:red;");
    errorLabel->hide();

    auto *layout = new QVBoxLayout(this);

    layout->addStretch();
    layout->addWidget(fullNameEdit);
    layout->addWidget(usernameEdit);
    layout->addWidget(passwordEdit);
    layout->addWidget(confirmPasswordEdit);

    auto *roleLayout = new QHBoxLayout;
    roleLayout->addWidget(listenerRadio);
    roleLayout->addWidget(artistRadio);

    auto *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(signupButton);
    buttonsLayout->addWidget(loginButton);

    layout->addLayout(roleLayout);
    layout->addWidget(errorLabel);
    layout->addLayout(buttonsLayout);
    layout->addStretch();
}


void RegisterPage::setupConnections() {
    connect(signupButton, &QPushButton::clicked, this, [this]() {
        clearError();

        if (!isValidPasswordFields()) return;

        const Role role = listenerRadio->isChecked() ? Role::Listener : Role::Artist;

        emit signupRequested(
            role,
            fullNameEdit->text().trimmed(),
            usernameEdit->text().trimmed(),
            passwordEdit->text()
        );
    });

    connect(loginButton, &QPushButton::clicked, this, &RegisterPage::loginPageRequested);
}


void RegisterPage::clearFields() {
    fullNameEdit->clear();
    usernameEdit->clear();
    passwordEdit->clear();
    confirmPasswordEdit->clear();

    listenerRadio->setChecked(true);

    clearError();
}


void RegisterPage::setError(const QString &message) {
    errorLabel->setText(message);
    errorLabel->show();
}


void RegisterPage::clearError() {
    errorLabel->clear();
    errorLabel->hide();
}


bool RegisterPage::isValidPasswordFields() {
    if (passwordEdit->text().isEmpty()) {
        setError("Password cannot be empty.");
        return false;
    }

    if (passwordEdit->text() != confirmPasswordEdit->text()) {
        setError("Passwords don\'t match.");
        return false;
    }

    return true;
}
