#include "AlbumPage.h"
#include <QVBoxLayout>
#include "../../Components/Cards/AlbumCard/AlbumCard.h"

AlbumPage::AlbumPage(QWidget *parent) : QWidget(parent) {
    setupUI();
}


void AlbumPage::setupUI() {
    albumsGrid = new CardGrid<AlbumCard, Album>("Albums", this);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(albumsGrid);
}


void AlbumPage::setAlbums(const QVector<Album> &albums) {
    albumsGrid->setItems(albums);

    const auto cards = findChildren<AlbumCard *>();
    for (auto *card: cards) {
        connect(card, &AlbumCard::clicked, this, &AlbumPage::albumClicked);
        connect(card, &AlbumCard::editRequested, this, &AlbumPage::albumEditRequested);
        connect(card, &AlbumCard::deleteRequested, this, &AlbumPage::albumDeleteRequested);
    }
}


void AlbumPage::hideEDButtons() {
    const auto cards = findChildren<AlbumCard *>();
    for (auto *card: cards) {
        card->hideEDButtons();
    }
}


void AlbumPage::showEDButtons() {
    const auto cards = findChildren<AlbumCard *>();
    for (auto *card: cards) {
        card->showEDButtons();
    }
}