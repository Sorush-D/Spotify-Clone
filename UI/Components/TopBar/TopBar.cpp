#include "TopBar.h"
#include <QHBoxLayout>
#include "../../../Services/AuthenticationService/AuthenticationService.h"

TopBar::TopBar(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
    refreshUserState();
}


void TopBar::setupUI() {
    logoButton = new QToolButton(this);
    logoButton->setIcon(QIcon(":/Icons/logo.png"));
    logoButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    logoButton->setAutoRaise(true);
    logoButton->setIconSize(QSize(32, 32));


    homeButton = new QToolButton(this);
    homeButton->setIcon(QIcon(":/Icons/home.png"));
    homeButton->setToolButtonStyle(Qt::ToolButtonIconOnly);
    homeButton->setAutoRaise(true);
    homeButton->setIconSize(QSize(32, 32));

    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("Search...");

    loginButton = new QPushButton("Login", this);
    registerButton = new QPushButton("Sign Up", this);

    profileButton = new QToolButton(this);
    profileButton->setText("Profile");
    profileButton->setIcon(QIcon(":/Icons/user.png"));
    profileButton->setIconSize(QSize(32, 32));

    profileMenu = new QMenu(this);
    profileAction = profileMenu->addAction("Profile");
    editProfileAction = profileMenu->addAction("Edit Profile");
    profileMenu->addSeparator();
    logoutAction = profileMenu->addAction("Logout");

    profileButton->setMenu(profileMenu);
    profileButton->setPopupMode(QToolButton::MenuButtonPopup);
    profileButton->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);

    auto *layout = new QHBoxLayout(this);

    layout->addWidget(logoButton);
    layout->addWidget(homeButton);

    layout->addWidget(searchEdit, 1);

    layout->addWidget(loginButton);
    layout->addWidget(registerButton);
    layout->addWidget(profileButton);
}


void TopBar::setupConnections() {
    connect(logoButton, &QToolButton::clicked, this, &TopBar::homeClicked);
    connect(homeButton, &QToolButton::clicked, this, &TopBar::homeClicked);

    connect(searchEdit, &QLineEdit::returnPressed, this, [this]() {
        emit searchRequested(searchEdit->text());
    });

    connect(loginButton, &QPushButton::clicked, this, &TopBar::loginClicked);
    connect(registerButton, &QPushButton::clicked, this, &TopBar::registerClicked);

    connect(profileButton, &QToolButton::clicked, this, &TopBar::profileClicked);
    connect(profileAction, &QAction::triggered, this, &TopBar::profileClicked);
    connect(editProfileAction, &QAction::triggered, this, &TopBar::editProfileClicked);
    connect(logoutAction, &QAction::triggered, this, &TopBar::logoutClicked);
}


void TopBar::refreshUserState() {
    auto &auth = AuthenticationService::instance();
    if (auth.isLoggedIn()) {
        loginButton->hide();
        registerButton->hide();

        profileButton->show();

        if (auth.currentArtist()) {
            profileButton->setText(auth.currentArtist()->getUserName());
            profileButton->setIcon(profileIcon(auth.currentArtist()->getProfilePicture()));
        } else if (auth.currentListener()) {
            profileButton->setText(auth.currentListener()->getUserName());
            profileButton->setIcon(profileIcon(auth.currentListener()->getProfilePicture()));
        }
    } else {
        loginButton->show();
        registerButton->show();

        profileButton->hide();
    }
}


QIcon TopBar::profileIcon(const QByteArray &image) const {
    QPixmap pixmap;
    if (image.isEmpty() || !pixmap.loadFromData(image)) return QIcon(":/Icons/user.png");
    return QIcon(pixmap);
}
