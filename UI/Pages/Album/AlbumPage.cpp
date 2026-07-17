#include "AlbumPage.h"
#include <QVBoxLayout>
#include "../../../Repositories/ArtistRepository/ArtistRepository.h"
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
}
