#include "AlbumCard.h"

#include <QPushButton>
#include <QVBoxLayout>
#include "../../../../Repositories/ArtistRepository/ArtistRepository.h"

AlbumCard::AlbumCard(const Album &a, QWidget *parent) : QFrame(parent) {
    setupUI();
    setupConnections();
    setAlbum(a);
}


void AlbumCard::setupUI() {
    setFrameShape(QFrame::StyledPanel);

    coverLabel = new QLabel(this);
    coverLabel->setFixedSize(90, 90);
    coverLabel->setScaledContents(true);
    coverLabel->setPixmap(QPixmap(":/Icons/album.png"));

    titleLabel = new QLabel(this);
    artistLabel = new QLabel(this);

    editButton = new QToolButton(this);
    editButton->setIcon(QIcon(":/Icons/edit.png"));
    editButton->setAutoRaise(true);

    deleteButton = new QToolButton(this);
    deleteButton->setIcon(QIcon(":/Icons/delete.png"));
    deleteButton->setAutoRaise(true);

    auto *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(editButton);
    buttonsLayout->addWidget(deleteButton);

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(coverLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(artistLabel);
    layout->addLayout(buttonsLayout);

    hideEDButtons();
}


void AlbumCard::setupConnections() {
    connect(editButton, &QToolButton::clicked, this, [this]() {
        emit editRequested(album.getID());
    });

    connect(deleteButton, &QToolButton::clicked, this, [this]() {
        emit deleteRequested(album.getID());
    });
}



void AlbumCard::setAlbum(const Album &newAlbum) {
    album = newAlbum;

    coverLabel->setPixmap(getCover(album.getCoverPicture()));
    titleLabel->setText(album.getTitle());

    const auto artist = ArtistRepository::instance().search(album.getArtistID());
    artistLabel->setText(artist.has_value() ? artist->getFullName() : "Unknown Artist");
}


Album AlbumCard::getAlbum() const {
    return album;
}


QPixmap AlbumCard::getCover(const QByteArray &image) const {
    QPixmap pixmap;
    if (image.isEmpty() || !pixmap.loadFromData(image)) return QPixmap(":/Icons/album.png");
    return pixmap;
}


void AlbumCard::mousePressEvent(QMouseEvent *event) {
    emit clicked(album.getID());
    QFrame::mousePressEvent(event);
}


void AlbumCard::hideEDButtons() {
    editButton->hide();
    deleteButton->hide();
}


void AlbumCard::showEDButtons() {
    editButton->show();
    deleteButton->show();
}