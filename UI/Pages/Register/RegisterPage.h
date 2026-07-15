#ifndef SPOTIFY_CLONE_REGISTER_H
#define SPOTIFY_CLONE_REGISTER_H
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>
#include <QRadioButton>
#include "../../../Entities/Account/Account.h"


class RegisterPage : public QWidget {
    Q_OBJECT
    QLineEdit *fullNameEdit;
    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;
    QLineEdit *confirmPasswordEdit;

    QRadioButton *listenerRadio;
    QRadioButton *artistRadio;

    QPushButton *signupButton;
    QPushButton *loginButton;

    QLabel *errorLabel;

    void setupUI();

    void setupConnections();

    bool isValidPasswordFields();

public:
    explicit RegisterPage(QWidget *parent = nullptr);

    void clearFields();

    void setError(const QString &);

    void clearError();

signals:
    void signupRequested(
        Role role,
        const QString &fullName,
        const QString &username,
        const QString &password
    );

    void loginPageRequested();
};


#endif
