#ifndef SPOTIFY_CLONE_SONGCARD_H
#define SPOTIFY_CLONE_SONGCARD_H
#include <QLabel>
#include <QToolButton>
#include <QFrame>
#include "../../../../Entities/Song/Song.h"


class SongCard : public QFrame {
    Q_OBJECT
    Song song;

    QLabel *coverLabel;
    QLabel *titleLabel;
    QLabel *artistLabel;

    QToolButton *playButton;
    QToolButton *likeButton;

    bool isLiked;
    bool isPlaying;

    void setupUI();

    void setupConnections();

    QPixmap getCover(const QByteArray &) const;

    void updatePlayIcon();

    void updateLikeIcon();

    void mousePressEvent(QMouseEvent *event) override;

public:
    explicit SongCard(const Song &, QWidget *parent = nullptr);

    void setSong(const Song &);

    Song getSong() const;

    void setPlaying(bool playing);

    void setLiked(bool liked);

signals:
    void playRequested(int songId);

    void likeRequested(int songId);

    void clicked(int songId);
};


#endif
