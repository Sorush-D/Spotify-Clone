#include "PlayerBar.h"
#include <QVBoxLayout>
#include "../../../Repositories/ArtistRepository/ArtistRepository.h"

PlayerBar::PlayerBar(QWidget *parent) : QWidget(parent) {
    setupUI();
    setupConnections();
}


void PlayerBar::setupUI() {
    coverLabel = new QLabel(this);
    coverLabel->setPixmap(QPixmap(":/Icons/album.png"));
    coverLabel->setFixedSize(56, 56);
    coverLabel->setScaledContents(true);

    titleLabel = new QLabel("No song", this);
    artistLabel = new QLabel("Unknown artist", this);

    likeButton = new QToolButton(this);
    likeButton->setIcon(QIcon(":/Icons/unlike.png"));

    previousButton = new QToolButton(this);
    previousButton->setIcon(QIcon(":/Icons/previous.png"));

    playPauseButton = new QToolButton(this);
    playPauseButton->setIcon(QIcon(":/Icons/play.png"));

    nextButton = new QToolButton(this);
    nextButton->setIcon(QIcon(":/Icons/next.png"));

    shuffleButton = new QToolButton(this);
    shuffleButton->setIcon(QIcon(":/Icons/shuffle.png"));

    loopButton = new QToolButton(this);
    loopButton->setIcon(QIcon(":/Icons/no_loop.png"));

    muteButton = new QToolButton(this);
    muteButton->setIcon(QIcon(":/Icons/volume.png"));

    currentTimeLabel = new QLabel("00:00", this);
    durationLabel = new QLabel("00:00", this);

    positionSlider = new QSlider(Qt::Horizontal, this);
    positionSlider->setRange(0, 0);
    positionSlider->setValue(0);

    volumeSlider = new QSlider(Qt::Horizontal, this);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(100);

    for (auto button: {
             previousButton,
             playPauseButton,
             nextButton,
             shuffleButton,
             loopButton,
             likeButton,
             muteButton
         }) {
        button->setAutoRaise(true);
        button->setIconSize(QSize(20, 20));
    }
    playPauseButton->setIconSize(QSize(32, 32));

    auto *songLayout = new QVBoxLayout;
    songLayout->addWidget(titleLabel);
    songLayout->addWidget(artistLabel);

    auto *leftLayout = new QHBoxLayout;
    leftLayout->addWidget(coverLabel);
    leftLayout->addLayout(songLayout);
    leftLayout->addWidget(likeButton);

    auto *controlLayout = new QHBoxLayout;
    controlLayout->addStretch();
    controlLayout->addWidget(previousButton);
    controlLayout->addWidget(playPauseButton);
    controlLayout->addWidget(nextButton);
    controlLayout->addWidget(loopButton);
    controlLayout->addWidget(shuffleButton);
    controlLayout->addStretch();

    auto *sliderLayout = new QHBoxLayout;
    sliderLayout->addWidget(currentTimeLabel);
    sliderLayout->addWidget(positionSlider);
    sliderLayout->addWidget(durationLabel);

    auto *centerLayout = new QVBoxLayout;
    centerLayout->addLayout(controlLayout);
    centerLayout->addLayout(sliderLayout);

    auto *rightLayout = new QHBoxLayout;
    rightLayout->addWidget(muteButton);
    rightLayout->addWidget(volumeSlider);

    auto *mainLayout = new QHBoxLayout(this);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(centerLayout, 1);
    mainLayout->addLayout(rightLayout);
}


void PlayerBar::setupConnections() {
    connect(previousButton, &QToolButton::clicked, this, &PlayerBar::previousClicked);
    connect(playPauseButton, &QToolButton::clicked, this, &PlayerBar::playPauseClicked);
    connect(nextButton, &QToolButton::clicked, this, &PlayerBar::nextClicked);

    connect(shuffleButton, &QToolButton::clicked, this, &PlayerBar::shuffleClicked);
    connect(loopButton, &QToolButton::clicked, this, &PlayerBar::loopClicked);
    connect(likeButton, &QToolButton::clicked, this, &PlayerBar::likeClicked);

    connect(positionSlider, &QSlider::sliderReleased, this, [this]() {
        emit positionChanged(positionSlider->value());
    });
    connect(volumeSlider, &QSlider::valueChanged, this, [this]() {
        emit volumeChanged(volumeSlider->value());
    });
}


void PlayerBar::setLiked(bool liked) {
    likeButton->setIcon(liked ? QIcon(":/Icons/like.png") : QIcon(":/Icons/unlike.png"));
}


void PlayerBar::setPlaying(bool playing) {
    playPauseButton->setIcon(playing ? QIcon(":/Icons/pause.png") : QIcon(":/Icons/play.png"));
}


void PlayerBar::setLoopMode(LoopCondition mode) {
    switch (mode) {
        case LoopCondition::Queue: loopButton->setIcon(QIcon(":/Icons/loop_queue.png"));
            break;
        case LoopCondition::Song: loopButton->setIcon(QIcon(":/Icons/loop_song.png"));
            break;
        case LoopCondition::None: loopButton->setIcon(QIcon(":/Icons/no_loop.png"));
            break;
    }
}


void PlayerBar::setVolume(int volume) {
    if (!(0 <= volume && volume <= 100)) return;

    volumeSlider->setValue(volume);
    setMute(volume == 0);
}


void PlayerBar::setMute(bool mute) {
    muteButton->setIcon(mute ? QIcon(":/Icons/mute.png") : QIcon(":/Icons/volume.png"));
}


void PlayerBar::setPosition(qint64 position) {
    positionSlider->setValue(static_cast<int>(position));
    currentTimeLabel->setText(formatTime(position));
}


void PlayerBar::setDuration(qint64 duration) {
    positionSlider->setMaximum(static_cast<int>(duration));
    durationLabel->setText(formatTime(duration));
}


void PlayerBar::setSong(const Song &song) {
    coverLabel->setPixmap(getCover(song.getCoverPicture()));

    titleLabel->setText(song.getTitle());

    const auto artist = ArtistRepository::instance().search(song.getArtistID());
    const QString artistName = artist.has_value() ? artist->getFullName() : QString("Unknown artist");
    artistLabel->setText(artistName);
}


QPixmap PlayerBar::getCover(const QByteArray &image) const {
    QPixmap pixmap;
    if (image.isEmpty() || !pixmap.loadFromData(image)) return QPixmap(":/Icons/album.png");
    return pixmap;
}


QString PlayerBar::formatTime(qint64 time) const {
    const int totalSeconds = static_cast<int>(time / 1000);
    const int seconds = totalSeconds % 60;
    const int minutes = totalSeconds / 60;

    return QString("%1:%2").arg(minutes, 2, 10, QChar('0')).arg(seconds, 2, 10, QChar('0'));
}
