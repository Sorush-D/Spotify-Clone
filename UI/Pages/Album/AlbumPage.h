#ifndef SPOTIFY_CLONE_ALBUMPAGE_H
#define SPOTIFY_CLONE_ALBUMPAGE_H
#include "../../Components/CardGrid/CardGrid.h"
#include "../../Components/Cards/SongCard/SongCard.h"
#include "../../../Entities/Album/Album.h"
#include <QWidget>


class AlbumPage : public QWidget {
    Q_OBJECT

    QLabel *coverLabel;
    QLabel *titleLabel;
    QLabel *artistLabel;

    CardGrid<SongCard, Song> *songsGrid;

    void setupUI();

    QPixmap getCover(const QByteArray &) const;

public:
    explicit AlbumPage(QWidget *parent = nullptr);

    void setAlbum(const Album &);

    void setSongs(const QVector<Song> &);
};


#endif
