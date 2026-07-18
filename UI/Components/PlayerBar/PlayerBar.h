#ifndef SPOTIFY_CLONE_PLAYERBAR_H
#define SPOTIFY_CLONE_PLAYERBAR_H
#include <QWidget>
#include <QLabel>
#include <QToolButton>
#include <QSlider>
#include <qwidget.h>
#include "../../../Services/PlayerService/PlayerService.h"


class PlayerBar : public QWidget {
    Q_OBJECT

    QLabel *coverLabel;

    QLabel *titleLabel;
    QLabel *artistLabel;

    QToolButton *likeButton;

    QToolButton *previousButton;
    QToolButton *playPauseButton;
    QToolButton *nextButton;

    QToolButton *shuffleButton;
    QToolButton *loopButton;

    QLabel *currentTimeLabel;
    QLabel *durationLabel;

    QSlider *positionSlider;

    QToolButton *muteButton;
    QSlider *volumeSlider;

    bool userSeeking = false;

    void setupUI();

    void setupConnections();

    [[nodiscard]] QPixmap getCover(const QByteArray &) const;

    [[nodiscard]] QString formatTime(qint64) const;

public:
    explicit PlayerBar(QWidget *parent = nullptr);

    void refresh();

    void setLiked(bool liked);

    void setPlaying(bool playing);

    void setLoopMode(LoopCondition mode);

    void setVolume(float volume);

    void setMute(bool mute);

    void setPosition(qint64 current);

    void setDuration(qint64 duration);

    void setSong(const Song &);

signals:
    void previousClicked();

    void playPauseClicked();

    void nextClicked();

    void shuffleClicked();

    void loopClicked();

    void likeClicked();

    void positionChanged(qint64 value);

    void volumeChanged(float value);
};


#endif
