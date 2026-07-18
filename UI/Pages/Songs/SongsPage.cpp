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

    const auto cards = findChildren<SongCard *>();
    for (auto *card: cards) {
        connect(card, &SongCard::clicked, this, &SongsPage::songClicked);
        connect(card, &SongCard::playRequested, this, &SongsPage::songPlayRequested);
        connect(card, &SongCard::likeRequested, this, &SongsPage::songLikeRequested);
        connect(card, &SongCard::editRequested, this, &SongsPage::songEditRequested);
        connect(card, &SongCard::deleteRequested, this, &SongsPage::songDeleteRequested);
    }
}


void SongsPage::setMode(SongsPageMode m) {
    mode = m;

    switch (mode) {
        case SongsPageMode::LikedSongs:
            songsGrid->setTitle("Liked Songs");
            hideEDButtons();
            break;
        case SongsPageMode::MySongs:
            songsGrid->setTitle("My Songs");
            showEDButtons();
            break;
        case SongsPageMode::MySingles:
            songsGrid->setTitle("My Singles");
            showEDButtons();
            break;
        case SongsPageMode::PlaylistSongs:
            songsGrid->setTitle("Playlist Songs");
            hideEDButtons();
            break;
        case SongsPageMode::AlbumSongs:
            songsGrid->setTitle("Album Songs");
            hideEDButtons();
            break;
    }
}


void SongsPage::showSongs(SongsPageMode m, const QVector<Song> &songs) {
    setSongs(songs);
    setMode(m);
}


void SongsPage::hideEDButtons() {
    const auto cards = findChildren<SongCard *>();
    for (auto *card: cards) {
        card->hideEDButtons();
    }
}


void SongsPage::showEDButtons() {
    const auto cards = findChildren<SongCard *>();
    for (auto *card: cards) {
        card->showEDButtons();
    }
}
