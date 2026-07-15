#include "PlayerService.h"
#include "../../Repositories/ListenerRepository/ListenerRepository.h"
#include "../../Repositories/SongRepository/SongRepository.h"
#include "../AuthenticationService/AuthenticationService.h"
#include "../ListenerService/ListenerService.h"
#include <random>

bool PlayerService::isValidIndex(int index) const {
    return 0 <= index && index < queue.size();
}


PlayerService::PlayerService()
    : player(new QMediaPlayer(this)),
      audioOutput(new QAudioOutput(this)),
      loopCondition(LoopCondition::None),
      currentIndex(-1),
      muted(false),
      liked(false) {
    player->setAudioOutput(audioOutput);

    connect(
        player,
        &QMediaPlayer::mediaStatusChanged,
        this,
        [this](QMediaPlayer::MediaStatus status) {
            if (status == QMediaPlayer::EndOfMedia)
                handleEndOfMedia();
        }
    );

    connect(
        player,
        &QMediaPlayer::positionChanged,
        this,
        &PlayerService::positionChanged
    );

    connect(
        player,
        &QMediaPlayer::durationChanged,
        this,
        &PlayerService::durationChanged
    );

    connect(
        player,
        &QMediaPlayer::playbackStateChanged,
        this,
        &PlayerService::playbackStateChanged
    );
}


PlayerService &PlayerService::instance() {
    static PlayerService instance;
    return instance;
}


void PlayerService::setQueue(const QVector<Song> &songs) {
    player->stop();
    player->setSource(QUrl());

    if (songs.isEmpty()) {
        clearQueue();
        return;
    }

    queue = songs;

    currentIndex = 0;

    liked = isLiked();
    emit likeChanged(liked);
    emit currentSongChanged(queue[currentIndex]);
}


void PlayerService::setLoopCondition(LoopCondition condition) {
    if (loopCondition == condition) return;

    loopCondition = condition;
    emit loopConditionChanged(loopCondition);
}


void PlayerService::setVolume(float volume) {
    if (!(0 <= volume && volume <= 1)) return;
    if (audioOutput->volume() == volume) return;

    audioOutput->setVolume(volume);
    if (muted != (volume == 0)) {
        muted = volume == 0;
        emit muteChanged(muted);
    }
    emit volumeChanged(volume);
}


LoopCondition PlayerService::getLoopCondition() const {
    return loopCondition;
}


float PlayerService::getVolume() const {
    return audioOutput->volume();
}


qint64 PlayerService::getPosition() const {
    return player->position();
}


qint64 PlayerService::getDuration() const {
    return player->duration();
}


QMediaPlayer::PlaybackState PlayerService::getPlaybackState() const {
    return player->playbackState();
}


std::optional<Song> PlayerService::currentSong() const {
    if (!isValidIndex(currentIndex)) return std::nullopt;

    return queue[currentIndex];
}


void PlayerService::play(int index) {
    if (!isValidIndex(index)) return;

    if (currentIndex != index) {
        currentIndex = index;
        liked = isLiked();
        emit likeChanged(liked);
        emit currentSongChanged(queue[currentIndex]);
    }

    const QString path = queue[currentIndex].getAudioFilePath();
    player->setSource(QUrl::fromLocalFile(path));

    player->play();
}


void PlayerService::resume() {
    if (!isValidIndex(currentIndex)) return;

    player->play();
}


void PlayerService::pause() {
    player->pause();
}


void PlayerService::stop() {
    player->stop();
}


void PlayerService::next() {
    if (!isValidIndex(currentIndex)) return;

    play((currentIndex + 1) % queue.size());
}


void PlayerService::previous() {
    if (!isValidIndex(currentIndex)) return;

    play(currentIndex == 0 ? queue.size() - 1 : currentIndex - 1);
}


void PlayerService::handleEndOfMedia() {
    if (!isValidIndex(currentIndex)) return;

    switch (loopCondition) {
        case LoopCondition::Queue:
            play((currentIndex + 1) % queue.size());
            break;

        case LoopCondition::Song:
            player->setPosition(0);
            player->play();
            break;

        case LoopCondition::None:
            if (currentIndex == queue.size() - 1) {
                stop();
                return;
            }
            play(currentIndex + 1);
    }
}


void PlayerService::seek(qint64 position) {
    if (0 <= position && position <= player->duration())
        player->setPosition(position);
}


bool PlayerService::isPlaying() const {
    return player->playbackState() == QMediaPlayer::PlayingState;
}


bool PlayerService::isLiked() const {
    if (!isValidIndex(currentIndex)) return false;

    const int songId = queue[currentIndex].getID();
    return ListenerService::instance().isSongLiked(songId);
}


void PlayerService::toggleLike() {
    if (!isValidIndex(currentIndex)) return;

    const int songId = queue[currentIndex].getID();
    liked = ListenerService::instance().toggleLike(songId);

    emit likeChanged(liked);
}


bool PlayerService::isMuted() const {
    return muted;
}


void PlayerService::shuffle() {
    if (queue.size() <= 1) return;

    std::shuffle(queue.begin(), queue.end(), std::default_random_engine{std::random_device{}()});
    currentIndex = -1;
    play(0);
}


void PlayerService::clearQueue() {
    queue.clear();
    player->setSource(QUrl());
    currentIndex = -1;
    liked = false;
    muted = false;
    emit likeChanged(false);
}


void PlayerService::closePlayer() {
    player->stop();
    clearQueue();

    emit playerClosed();
}
