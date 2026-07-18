#include "PlaylistCard.h"
#include <QVBoxLayout>
#include "../../../../Repositories/ListenerRepository/ListenerRepository.h"

PlaylistCard::PlaylistCard(const Playlist &p, QWidget *parent) : QFrame(parent) {
    setupUI();
    setupConnections();
    setPlaylist(p);
}


void PlaylistCard::setupUI() {
    setFrameShape(QFrame::StyledPanel);
    setFixedSize(120, 200);

    coverLabel = new QLabel(this);
    coverLabel->setFixedSize(100, 100);
    coverLabel->setScaledContents(true);
    coverLabel->setPixmap(QPixmap(":/Icons/playlist.png"));

    titleLabel = new QLabel(this);
    ownerLabel = new QLabel(this);

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

    layout->addWidget(coverLabel, 0, Qt::AlignHCenter);
    layout->addWidget(titleLabel);
    layout->addWidget(ownerLabel);
    layout->addLayout(buttonsLayout);

    hideEDButtons();
}


void PlaylistCard::setupConnections() {
    connect(editButton, &QToolButton::clicked, this, [this]() {
        emit editRequested(playlist.getID());
    });

    connect(deleteButton, &QToolButton::clicked, this, [this]() {
        emit deleteRequested(playlist.getID());
    });
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


void PlaylistCard::hideEDButtons() {
    editButton->hide();
    deleteButton->hide();
}


void PlaylistCard::showEDButtons() {
    editButton->show();
    deleteButton->show();
}
