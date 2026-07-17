#ifndef SPOTIFY_CLONE_SIDEBAR_H
#define SPOTIFY_CLONE_SIDEBAR_H
#include <QPushButton>
#include <qwidget.h>


class SideBar : public QWidget {
    Q_OBJECT

    QPushButton *likedSongsButton;
    QPushButton *playlistsButton;

    QPushButton *mySongsButton;
    QPushButton *mySinglesButton;
    QPushButton *myAlbumsButton;

    QPushButton *createSongButton;
    QPushButton *createAlbumButton;
    QPushButton *createPlaylistButton;

    void setupUI();

    void setupConnections();

    void hideListener();

    void showListener();

    void hideArtist();

    void showArtist();

public:
    explicit SideBar(QWidget *parent = nullptr);

    void refreshUserState();

signals:
    void likedSongsClicked();

    void playlistsClicked();

    void mySongsClicked();

    void mySinglesClicked();

    void myAlbumsClicked();

    void createSongClicked();

    void createAlbumClicked();

    void createPlaylistClicked();
};


#endif
