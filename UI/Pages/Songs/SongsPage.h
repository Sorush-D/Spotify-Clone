#ifndef SPOTIFY_CLONE_SONGSPAGE_H
#define SPOTIFY_CLONE_SONGSPAGE_H
#include "../../Components/CardGrid/CardGrid.h"
#include "../../Components/Cards/SongCard/SongCard.h"
#include <QWidget>


enum class SongsPageMode {
    LikedSongs,
    MySongs,
    MySingles,
    PlaylistSongs,
    AlbumSongs
};


class SongsPage : public QWidget {
    Q_OBJECT

    SongsPageMode mode;
    CardGrid<SongCard, Song> *songsGrid;

    void setupUI();

    void setMode(SongsPageMode mode);

    void setSongs(const QVector<Song> &songs);

public:
    explicit SongsPage(QWidget *parent = nullptr);

    void showSongs(SongsPageMode, const QVector<Song> &);

    void hideEDButtons();

    void showEDButtons();

signals:
    void songClicked(int songId);

    void songPlayRequested(int songId);

    void songLikeRequested(int songId);

    void songEditRequested(int songId);

    void songDeleteRequested(int songId);
};


#endif
