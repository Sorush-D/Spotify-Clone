#include "HomePage.h"

HomePage::HomePage(QWidget *parent) : QWidget(parent) {
    albumsList = new CardList<AlbumCard, Album>("Albums", this);
    artistsList = new CardList<ArtistCard, Artist>("Artists", this);
    songsList = new CardList<SongCard, Song>("Songs", this);

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(albumsList);
    layout->addWidget(artistsList);
    layout->addWidget(songsList);
}


void HomePage::setAlbums(const QVector<Album> &albums) {
    albumsList->setItems(albums);

    const auto cards = findChildren<AlbumCard *>();
    for (auto *card: cards)
        connect(card, &AlbumCard::clicked, this, &HomePage::albumClicked);
}


void HomePage::setArtists(const QVector<Artist> &artists) {
    artistsList->setItems(artists);

    const auto cards = findChildren<ArtistCard *>();
    for (auto *card: cards)
        connect(card, &ArtistCard::clicked, this, &HomePage::artistClicked);
}


void HomePage::setSongs(const QVector<Song> &songs) {
    songsList->setItems(songs);

    const auto cards = findChildren<SongCard *>();
    for (auto *card: cards) {
        connect(card, &SongCard::clicked, this, &HomePage::songClicked);
        connect(card, &SongCard::playRequested, this, &HomePage::songPlayRequested);
        connect(card, &SongCard::likeRequested, this, &HomePage::songLikeRequested);
    }
}
