#include "SongsPage.h"
#include <QVBoxLayout>

SongsPage::SongsPage(QWidget *parent) : QWidget(parent), mode(SongsPageMode::LikedSongs) {
    setupUI();
}


void SongsPage::setupUI() {
    songsGrid = new CardGrid<SongCard, Song>("Songs", this);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(songsGrid);
}


void SongsPage::setSongs(const QVector<Song> &songs) {
    songsGrid->setItems(songs);
}


void SongsPage::setMode(SongsPageMode m) {
    mode = m;

    switch (mode) {
        case SongsPageMode::LikedSongs:
            songsGrid->setTitle("Liked Songs");
            break;
        case SongsPageMode::MySongs:
            songsGrid->setTitle("My Songs");
            break;
        case SongsPageMode::MySingles:
            songsGrid->setTitle("My Singles");
            break;
        case SongsPageMode::PlaylistSongs:
            songsGrid->setTitle("Playlist Songs");
            break;
        case SongsPageMode::AlbumSongs:
            songsGrid->setTitle("Album Songs");
            break;
    }
}


void SongsPage::showSongs(SongsPageMode m, const QVector<Song> &songs) {
    setMode(m);
    setSongs(songs);
}
