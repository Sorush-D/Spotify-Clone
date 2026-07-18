#include "SongCard.h"
#include <QHBoxLayout>
#include "../../../../Repositories/ArtistRepository/ArtistRepository.h"
#include "../../../../Services/ListenerService/ListenerService.h"

SongCard::SongCard(const Song &s, QWidget *parent) : QFrame(parent), isLiked(false), isPlaying(false) {
    setupUI();
    setupConnections();
    setSong(s);
}


void SongCard::setupUI() {
    setFrameShape(QFrame::StyledPanel);
    setFixedSize(120, 200);

    coverLabel = new QLabel(this);
    coverLabel->setFixedSize(100, 100);
    coverLabel->setScaledContents(true);
    coverLabel->setPixmap(QPixmap(":/Icons/album.png"));

    titleLabel = new QLabel(this);
    artistLabel = new QLabel(this);

    playButton = new QToolButton(this);
    playButton->setIcon(QIcon(":/Icons/play.png"));
    playButton->setAutoRaise(true);

    likeButton = new QToolButton(this);
    likeButton->setIcon(QIcon(":/Icons/unlike.png"));
    likeButton->setAutoRaise(true);

    editButton = new QToolButton(this);
    editButton->setIcon(QIcon(":/Icons/edit.png"));
    editButton->setAutoRaise(true);

    deleteButton = new QToolButton(this);
    deleteButton->setIcon(QIcon(":/Icons/delete.png"));
    deleteButton->setAutoRaise(true);

    auto *buttonsLayout = new QHBoxLayout;
    buttonsLayout->addWidget(playButton);
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(likeButton);
    buttonsLayout->addWidget(editButton);
    buttonsLayout->addWidget(deleteButton);

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(coverLabel, 0, Qt::AlignHCenter);
    layout->addWidget(titleLabel);
    layout->addWidget(artistLabel);
    layout->addLayout(buttonsLayout);

    hideEDButtons();
}


void SongCard::setupConnections() {
    connect(playButton, &QToolButton::clicked, this, [this]() {
        emit playRequested(song.getID());
    });

    connect(likeButton, &QToolButton::clicked, this, [this]() {
        setLiked(!ListenerService::instance().isSongLiked(song.getID()));
        emit likeRequested(song.getID());
    });

    connect(editButton, &QToolButton::clicked, this, [this]() {
        emit editRequested(song.getID());
    });

    connect(deleteButton, &QToolButton::clicked, this, [this]() {
        emit deleteRequested(song.getID());
    });
}


void SongCard::setSong(const Song &newSong) {
    song = newSong;

    coverLabel->setPixmap(getCover(song.getCoverPicture()));
    titleLabel->setText(song.getTitle());

    const auto artist = ArtistRepository::instance().search(song.getArtistID());
    artistLabel->setText(artist.has_value() ? artist->getFullName() : "Unknown Artist");

    setLiked(ListenerService::instance().isSongLiked(song.getID()));
    setPlaying(false);
}


Song SongCard::getSong() const {
    return song;
}


QPixmap SongCard::getCover(const QByteArray &image) const {
    QPixmap pixmap;
    if (image.isEmpty() || !pixmap.loadFromData(image)) return QPixmap(":/Icons/album.png");
    return pixmap;
}


void SongCard::setPlaying(bool playing) {
    isPlaying = playing;
    updatePlayIcon();
}


void SongCard::updatePlayIcon() {
    playButton->setIcon(isPlaying ? QIcon(":/Icons/pause.png") : QIcon(":/Icons/play.png"));
}


void SongCard::setLiked(bool liked) {
    isLiked = liked;
    updateLikeIcon();
}


void SongCard::updateLikeIcon() {
    likeButton->setIcon(isLiked ? QIcon(":/Icons/like.png") : QIcon(":/Icons/unlike.png"));
}


void SongCard::mousePressEvent(QMouseEvent *event) {
    emit clicked(song.getID());
    QFrame::mousePressEvent(event);
}


void SongCard::hideEDButtons() {
    editButton->hide();
    deleteButton->hide();
}


void SongCard::showEDButtons() {
    editButton->show();
    deleteButton->show();
}
