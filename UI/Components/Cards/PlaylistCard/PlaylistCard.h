#ifndef SPOTIFY_CLONE_PLAYLISTCARD_H
#define SPOTIFY_CLONE_PLAYLISTCARD_H
#include <QLabel>
#include <QFrame>
#include <QToolButton>
#include "../../../../Entities/Playlist/Playlist.h"

class PlaylistCard : public QFrame {
    Q_OBJECT

    Playlist playlist;

    QLabel *coverLabel;
    QLabel *titleLabel;
    QLabel *ownerLabel;

    QToolButton *editButton;
    QToolButton *deleteButton;

    void setupUI();

    void setupConnections();

    void mousePressEvent(QMouseEvent *) override;

public:
    explicit PlaylistCard(const Playlist &, QWidget *parent = nullptr);

    void setPlaylist(const Playlist &);

    Playlist getPlaylist() const;

    void hideEDButtons();

    void showEDButtons();

signals:
    void clicked(int playlistId);

    void editRequested(int playlistId);

    void deleteRequested(int playlistId);
};


#endif
