#include "ArtistPage.h"

ArtistPage::ArtistPage(QWidget *parent) : QWidget(parent) {
    setupUI();
}


void ArtistPage::setupUI() {
    pictureLabel = new QLabel(this);
    pictureLabel->setFixedSize(250, 250);
    pictureLabel->setScaledContents(true);
    pictureLabel->setPixmap(QPixmap(":/Icons/user.png"));

    nameLabel = new QLabel(this);
    bioLabel = new QLabel(this);
    bioLabel->setWordWrap(true);

    albumsList = new CardList<AlbumCard, Album>("Albums", this);
    songsList = new CardList<SongCard, Song>("Songs", this);

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(pictureLabel, 0, Qt::AlignCenter);
    layout->addWidget(nameLabel, 0, Qt::AlignCenter);
    layout->addWidget(bioLabel, 0, Qt::AlignCenter);

    layout->addWidget(albumsList);
    layout->addWidget(songsList);
}


void ArtistPage::setArtist(const Artist &artist) {
    pictureLabel->setPixmap(getProfilePicture(artist.getProfilePicture()));

    nameLabel->setText(artist.getFullName());
    bioLabel->setText(artist.getBiography());
}


void ArtistPage::setAlbums(const QVector<Album> &albums) {
    albumsList->setItems(albums);
}


void ArtistPage::setSongs(const QVector<Song> &songs) {
    songsList->setItems(songs);
}


QPixmap ArtistPage::getProfilePicture(const QByteArray &image) const {
    QPixmap pixmap;
    if (image.isEmpty() || !pixmap.loadFromData(image)) return QPixmap(":/Icons/user.png");
    return pixmap;
}
