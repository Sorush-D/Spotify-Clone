#ifndef SPOTIFY_CLONE_TOPBAR_H
#define SPOTIFY_CLONE_TOPBAR_H
#include <QPushButton>
#include <QLineEdit>
#include <QToolButton>
#include <QMenu>
#include <qwidget.h>


class TopBar : public QWidget {
    Q_OBJECT
    QToolButton *logoButton;
    QToolButton *homeButton;

    QLineEdit *searchEdit;

    QPushButton *loginButton;
    QPushButton *registerButton;

    QToolButton *profileButton;

    QMenu *profileMenu;
    QAction *profileAction;
    QAction *editProfileAction;
    QAction *logoutAction;

    void setupUI();

    void setupConnections();

    QIcon profileIcon(const QByteArray &) const;

public:
    explicit TopBar(QWidget *parent = nullptr);

    void refreshUserState();

signals:
    void homeClicked();

    void searchRequested(const QString &);

    void loginClicked();

    void registerClicked();

    void profileClicked();

    void editProfileClicked();

    void logoutClicked();
};


#endif
