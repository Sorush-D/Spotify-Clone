#ifndef SPOTIFY_CLONE_LIKEDSONGSPAGE_H
#define SPOTIFY_CLONE_LIKEDSONGSPAGE_H
#include "../../Components/CardGrid/CardGrid.h"
#include "../../Components/Cards/SongCard/SongCard.h"
#include <QWidget>


class LikedSongsPage : public QWidget {
    Q_OBJECT

    CardGrid<SongCard, Song> *songsGrid;

    void setupUI();

public:
    explicit LikedSongsPage(QWidget *parent = nullptr);

    void setSongs(const QVector<Song> &songs);
};


#endif
