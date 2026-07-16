#include "LikedSongsPage.h"
#include <QVBoxLayout>

LikedSongsPage::LikedSongsPage(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void LikedSongsPage::setupUI() {
    songsGrid = new CardGrid<SongCard, Song>("Liked Songs", this);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(songsGrid);
}

void LikedSongsPage::setSongs(const QVector<Song> &songs) {
    songsGrid->setItems(songs);
}
