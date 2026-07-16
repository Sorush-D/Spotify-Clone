#include "HomePage.h"

HomePage::HomePage(QWidget *parent) : QWidget(parent) {
    albumsList = new CardList<AlbumCard, Album>("Albums", {}, this);
    artistsList = new CardList<ArtistCard, Artist>("Artists", {}, this);
    songsList = new CardList<SongCard, Song>("Songs", {}, this);

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(albumsList);
    layout->addWidget(artistsList);
    layout->addWidget(songsList);
}


void HomePage::setAlbums(const QVector<Album> &albums) {
    albumsList->setItems(albums);
}


void HomePage::setArtists(const QVector<Artist> &artists) {
    artistsList->setItems(artists);
}


void HomePage::setSongs(const QVector<Song> &songs) {
    songsList->setItems(songs);
}
