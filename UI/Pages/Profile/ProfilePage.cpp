#include "ProfilePage.h"
#include <QVBoxLayout>
#include <QPixmap>

ProfilePage::ProfilePage(QWidget *parent) : QWidget(parent) {
    setupUI();
}


void ProfilePage::setupUI() {
    pictureLabel = new QLabel(this);
    pictureLabel->setFixedSize(200, 200);
    pictureLabel->setScaledContents(true);
    pictureLabel->setPixmap(QPixmap(":/Icons/user.png"));

    fullNameLabel = new QLabel(this);
    usernameLabel = new QLabel(this);
    roleLabel = new QLabel(this);

    editProfileButton = new QPushButton("Edit Profile", this);

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(pictureLabel, 0, Qt::AlignCenter);
    layout->addWidget(fullNameLabel, 0, Qt::AlignCenter);
    layout->addWidget(usernameLabel, 0, Qt::AlignCenter);
    layout->addWidget(roleLabel, 0, Qt::AlignCenter);
    layout->addWidget(editProfileButton, 0, Qt::AlignCenter);
    layout->addStretch();

    connect(editProfileButton, &QPushButton::clicked, this, &ProfilePage::editProfileRequested);
}


void ProfilePage::setArtist(const Artist &artist) {
    pictureLabel->setPixmap(getProfilePicture(artist.getProfilePicture()));
    fullNameLabel->setText(artist.getFullName());
    usernameLabel->setText(artist.getUserName());
    roleLabel->setText("Artist");
}


void ProfilePage::setListener(const Listener &listener) {
    pictureLabel->setPixmap(getProfilePicture(listener.getProfilePicture()));
    fullNameLabel->setText(listener.getFullName());
    usernameLabel->setText(listener.getUserName());
    roleLabel->setText("Listener");
}


QPixmap ProfilePage::getProfilePicture(const QByteArray &image) const {
    QPixmap pixmap;
    if (image.isEmpty() || !pixmap.loadFromData(image)) return QPixmap(":/Icons/user.png");
    return pixmap;
}
