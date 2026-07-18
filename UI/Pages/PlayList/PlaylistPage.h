#ifndef SPOTIFY_CLONE_PLAYLISTPAGE_H
#define SPOTIFY_CLONE_PLAYLISTPAGE_H
#include "../../Components/CardGrid/CardGrid.h"
#include "../../../Entities/Playlist/Playlist.h"
#include "../../Components/Cards/PlaylistCard/PlaylistCard.h"
#include <QLabel>
#include <QVector>
#include <QWidget>


class PlaylistPage : public QWidget {
    Q_OBJECT

    CardGrid<PlaylistCard, Playlist> *playlistsGrid;

    void setupUI();

public:
    explicit PlaylistPage(QWidget *parent = nullptr);

    void setPlaylists(const QVector<Playlist> &);

    void hideEDButtons();

    void showEDButtons();

signals:
    void playlistClicked(int playlistId);

    void playlistEditRequested(int playlistId);

    void playlistDeleteRequested(int playlistId);
};


#endif
