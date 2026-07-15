#ifndef SPOTIFY_CLONE_PLAYLISTCARD_H
#define SPOTIFY_CLONE_PLAYLISTCARD_H
#include <QLabel>
#include <QFrame>
#include "../../../../Entities/Playlist/Playlist.h"

class PlaylistCard : public QFrame {
    Q_OBJECT

    Playlist playlist;

    QLabel *coverLabel;
    QLabel *titleLabel;
    QLabel *ownerLabel;

    void setupUI();

    void mousePressEvent(QMouseEvent *) override;

public:
    explicit PlaylistCard(const Playlist &, QWidget *parent = nullptr);

    void setPlaylist(const Playlist &);

    Playlist getPlaylist() const;

signals:
    void clicked(int playlistId);
};


#endif
