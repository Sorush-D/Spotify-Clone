#ifndef SPOTIFY_CLONE_PLAYLISTPAGE_H
#define SPOTIFY_CLONE_PLAYLISTPAGE_H
#include "../../../Entities/Playlist/Playlist.h"
#include "../../Components/CardGrid/CardGrid.h"
#include "../../Components/Cards/SongCard/SongCard.h"
#include <QLabel>
#include <QVector>
#include <QWidget>


class PlaylistPage : public QWidget {
    Q_OBJECT

    QLabel *titleLabel;
    CardGrid<SongCard, Song> *songsGrid;

    void setupUI();

public:
    explicit PlaylistPage(QWidget *parent = nullptr);

    void setPlaylist(const Playlist &);

    void setSongs(const QVector<Song> &);
};


#endif
