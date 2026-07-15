#include "PlaylistCard.h"
#include <QVBoxLayout>
#include "../../../../Repositories/ListenerRepository/ListenerRepository.h"

PlaylistCard::PlaylistCard(const Playlist &p, QWidget *parent) : QFrame(parent) {
    setupUI();
    setPlaylist(p);
}


void PlaylistCard::setupUI() {
    setFrameShape(QFrame::StyledPanel);

    coverLabel = new QLabel(this);
    coverLabel->setFixedSize(90, 90);
    coverLabel->setScaledContents(true);
    coverLabel->setPixmap(QPixmap(":/Icons/playlist.png"));

    titleLabel = new QLabel(this);
    ownerLabel = new QLabel(this);

    auto *layout = new QVBoxLayout(this);

    layout->addWidget(coverLabel);
    layout->addWidget(titleLabel);
    layout->addWidget(ownerLabel);
}


void PlaylistCard::setPlaylist(const Playlist &newPlaylist) {
    playlist = newPlaylist;

    titleLabel->setText(playlist.getTitle());

    const auto owner = ListenerRepository::instance().search(playlist.getListenerID());
    ownerLabel->setText(owner.has_value() ? owner->getFullName() : "Unknown User");
}


Playlist PlaylistCard::getPlaylist() const {
    return playlist;
}


void PlaylistCard::mousePressEvent(QMouseEvent *event) {
    emit clicked(playlist.getID());
    QFrame::mousePressEvent(event);
}
