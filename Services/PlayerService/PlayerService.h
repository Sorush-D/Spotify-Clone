#ifndef SPOTIFY_CLONE_PLAYERSERVICE_H
#define SPOTIFY_CLONE_PLAYERSERVICE_H
#include "../../Entities/Song/Song.h"
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QAudioOutput>
#include <QVector>


enum class LoopCondition {
    Queue,
    Song,
    None
};


class PlayerService : public QObject {
    Q_OBJECT

    QMediaPlayer *player;
    QAudioOutput *audioOutput;

    QVector<Song> queue;
    LoopCondition loopCondition;
    int currentIndex;

    bool isValidIndex(int index) const;

    PlayerService();

    void handleEndOfMedia();

public:
    PlayerService(const PlayerService &) = delete;

    PlayerService &operator=(const PlayerService &) = delete;

    static PlayerService &instance();

    void setQueue(const QVector<Song> &songs);

    void setLoopCondition(LoopCondition condition);

    void setVolume(float volume);

    LoopCondition getLoopCondition() const;

    float getVolume() const;

    qint64 getPosition() const;

    qint64 getDuration() const;

    QMediaPlayer::PlaybackState getPlaybackState() const;

    std::optional<Song> currentSong() const;

    void play(int index);

    void resume();

    void pause();

    void stop();

    void next();

    void previous();

    void seek(qint64 position);

signals:
    void currentSongChanged();

    void volumeChanged(float volume);

    void positionChanged(qint64 position);

    void durationChanged(qint64 duration);

    void playbackStateChanged(QMediaPlayer::PlaybackState state);

    void loopConditionChanged(LoopCondition condition);
};


#endif
