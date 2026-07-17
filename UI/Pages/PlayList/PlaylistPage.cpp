#include "PlaylistPage.h"
#include <QVBoxLayout>

PlaylistPage::PlaylistPage(QWidget *parent) : QWidget(parent) {
    setupUI();
}


void PlaylistPage::setupUI() {
    playlistsGrid = new CardGrid<PlaylistCard, Playlist>("Playlists", this);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(playlistsGrid);
}


void PlaylistPage::setPlaylists(const QVector<Playlist> &playlists) {
    playlistsGrid->setItems(playlists);

    const auto cards = findChildren<PlaylistCard *>();
    for (auto *card: cards)
        connect(card, &PlaylistCard::clicked, this, &PlaylistPage::playlistClicked);
}
