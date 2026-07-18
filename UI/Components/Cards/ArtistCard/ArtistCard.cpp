#include "ArtistCard.h"
#include <QVBoxLayout>

ArtistCard::ArtistCard(const Artist &a, QWidget *parent) : QFrame(parent) {
    setupUI();
    setArtist(a);
}


void ArtistCard::setupUI() {
    setFrameShape(QFrame::StyledPanel);
    setFixedSize(120, 180);

    pictureLabel = new QLabel(this);
    pictureLabel->setFixedSize(100, 100);
    pictureLabel->setScaledContents(true);
    pictureLabel->setPixmap(QPixmap(":/Icons/user.png"));

    nameLabel = new QLabel(this);

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(pictureLabel, 0, Qt::AlignCenter);
    layout->addWidget(nameLabel);
}


void ArtistCard::setArtist(const Artist &newArtist) {
    artist = newArtist;

    pictureLabel->setPixmap(getImage(artist.getProfilePicture()));
    nameLabel->setText(artist.getFullName());
}


Artist ArtistCard::getArtist() const {
    return artist;
}


QPixmap ArtistCard::getImage(const QByteArray &image) const {
    QPixmap pixmap;
    if (image.isEmpty() || !pixmap.loadFromData(image)) return QPixmap(":/Icons/user.png");
    return pixmap;
}


void ArtistCard::mousePressEvent(QMouseEvent *event) {
    emit clicked(artist.getID());
    QFrame::mousePressEvent(event);
}
