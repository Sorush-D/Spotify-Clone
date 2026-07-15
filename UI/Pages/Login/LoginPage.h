#ifndef SPOTIFY_CLONE_LOGIN_H
#define SPOTIFY_CLONE_LOGIN_H
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QWidget>


class LoginPage : public QWidget {
    Q_OBJECT

    QLineEdit *usernameEdit;
    QLineEdit *passwordEdit;

    QPushButton *loginButton;
    QPushButton *signupButton;

    QLabel *errorLabel;

    void setupUI();

    void setupConnections();

public:
    explicit LoginPage(QWidget *parent = nullptr);

    void clearFields();

    void setError(const QString &);

    void clearError();

signals:
    void loginRequested(
        const QString &username,
        const QString &password
    );

    void signupRequested();
};


#endif
