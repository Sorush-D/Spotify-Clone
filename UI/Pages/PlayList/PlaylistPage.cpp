#include "PlaylistPage.h"
#include <QVBoxLayout>

PlaylistPage::PlaylistPage(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void PlaylistPage::setupUI() {
    titleLabel = new QLabel(this);
    songsGrid = new CardGrid<SongCard, Song>("Songs", this);

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(titleLabel, 0, Qt::AlignCenter);
    layout->addWidget(songsGrid);
}

void PlaylistPage::setPlaylist(const Playlist &playlist) {
    titleLabel->setText(playlist.getTitle());
}

void PlaylistPage::setSongs(const QVector<Song> &songs) {
    songsGrid->setItems(songs);
}
