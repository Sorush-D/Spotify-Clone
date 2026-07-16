#include "AlbumPage.h"
#include <QVBoxLayout>
#include "../../../Repositories/ArtistRepository/ArtistRepository.h"

AlbumPage::AlbumPage(QWidget *parent) : QWidget(parent) {
    setupUI();
}


void AlbumPage::setupUI() {
    coverLabel = new QLabel(this);
    coverLabel->setFixedSize(250, 250);
    coverLabel->setScaledContents(true);
    coverLabel->setPixmap(QPixmap(":/Icons/album.png"));

    titleLabel = new QLabel(this);
    artistLabel = new QLabel(this);

    songsGrid = new CardGrid<SongCard, Song>("Songs", this);

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(coverLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(artistLabel);

    layout->addWidget(songsGrid);
}


void AlbumPage::setAlbum(const Album &album) {
    coverLabel->setPixmap(getCover(album.getCoverPicture()));
    titleLabel->setText(album.getTitle());

    const auto artist = ArtistRepository::instance().search(album.getArtistID());
    artistLabel->setText(artist.has_value() ? artist->getFullName() : "Unknown Artist");
}


void AlbumPage::setSongs(const QVector<Song> &songs) {
    songsGrid->setItems(songs);
}


QPixmap AlbumPage::getCover(const QByteArray &image) const {
    QPixmap pixmap;
    if (image.isEmpty() || !pixmap.loadFromData(image)) return QPixmap(":/Icons/album.png");
    return pixmap;
}
