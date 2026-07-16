#ifndef SPOTIFY_CLONE_PROFILEPAGE_H
#define SPOTIFY_CLONE_PROFILEPAGE_H
#include "../../../Entities/Artist/Artist.h"
#include "../../../Entities/Listener/Listener.h"
#include <QLabel>
#include <QPushButton>
#include <QWidget>


class ProfilePage : public QWidget {
    Q_OBJECT

    QLabel *pictureLabel;

    QLabel *fullNameLabel;
    QLabel *usernameLabel;
    QLabel *roleLabel;

    QPushButton *editProfileButton;

    void setupUI();

    QPixmap getProfilePicture(const QByteArray &) const;

public:
    explicit ProfilePage(QWidget *parent = nullptr);

    void setArtist(const Artist &);

    void setListener(const Listener &);

signals:
    void editProfileRequested();
};


#endif
