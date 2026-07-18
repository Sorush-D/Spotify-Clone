#include "SideBar.h"
#include <QVBoxLayout>
#include "../../../Services/AuthenticationService/AuthenticationService.h"

SideBar::SideBar(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
    refreshUserState();
}


void SideBar::setupUI() {
    likedSongsButton = new QPushButton("Liked Songs", this);
    likedSongsButton->setIcon(QIcon(":/Icons/liked_songs.png"));
    playlistsButton = new QPushButton("Playlists", this);
    playlistsButton->setIcon(QIcon(":/Icons/playlist.png"));

    mySongsButton = new QPushButton("My Songs", this);
    mySongsButton->setIcon(QIcon(":/Icons/album.png"));
    mySinglesButton = new QPushButton("My Singles", this);
    mySinglesButton->setIcon(QIcon(":/Icons/album.png"));
    myAlbumsButton = new QPushButton("My Albums", this);
    myAlbumsButton->setIcon(QIcon(":/Icons/album.png"));

    createSongButton = new QPushButton("Create Song", this);
    createSongButton->setIcon(QIcon(":/Icons/create.png"));
    createAlbumButton = new QPushButton("Create Album", this);
    createAlbumButton->setIcon(QIcon(":/Icons/create.png"));

    createPlaylistButton = new QPushButton("Create Playlist", this);
    createPlaylistButton->setIcon(QIcon(":/Icons/create.png"));

    for (auto *button: {
             likedSongsButton,
             playlistsButton,
             mySongsButton,
             mySinglesButton,
             myAlbumsButton,
             createSongButton,
             createAlbumButton,
             createPlaylistButton
         }) {
        button->setIconSize(QSize(28, 28));
    }

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(likedSongsButton);
    layout->addWidget(playlistsButton);

    layout->addWidget(mySongsButton);
    layout->addWidget(mySinglesButton);
    layout->addWidget(myAlbumsButton);

    layout->addWidget(createSongButton);
    layout->addWidget(createAlbumButton);
    layout->addWidget(createPlaylistButton);

    layout->addStretch();
}


void SideBar::setupConnections() {
    connect(likedSongsButton, &QPushButton::clicked, this, &SideBar::likedSongsClicked);
    connect(playlistsButton, &QPushButton::clicked, this, &SideBar::playlistsClicked);

    connect(mySongsButton, &QPushButton::clicked, this, &SideBar::mySongsClicked);
    connect(mySinglesButton, &QPushButton::clicked, this, &SideBar::mySinglesClicked);
    connect(myAlbumsButton, &QPushButton::clicked, this, &SideBar::myAlbumsClicked);

    connect(createSongButton, &QPushButton::clicked, this, &SideBar::createSongClicked);
    connect(createAlbumButton, &QPushButton::clicked, this, &SideBar::createAlbumClicked);

    connect(createPlaylistButton, &QPushButton::clicked, this, &SideBar::createPlaylistClicked);
}


void SideBar::refreshUserState() {
    auto &auth = AuthenticationService::instance();

    hideArtist();
    hideListener();

    if (auth.currentArtist()) {
        showArtist();
    } else if (auth.currentListener()) {
        showListener();
    }
}


void SideBar::hideListener() {
    likedSongsButton->hide();
    playlistsButton->hide();

    createPlaylistButton->hide();
}


void SideBar::showListener() {
    likedSongsButton->show();
    playlistsButton->show();

    createPlaylistButton->show();
}


void SideBar::hideArtist() {
    mySongsButton->hide();
    mySinglesButton->hide();
    myAlbumsButton->hide();

    createSongButton->hide();
    createAlbumButton->hide();
}


void SideBar::showArtist() {
    mySongsButton->show();
    mySinglesButton->show();
    myAlbumsButton->show();

    createSongButton->show();
    createAlbumButton->show();
}
