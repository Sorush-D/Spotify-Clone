#ifndef SPOTIFY_CLONE_HOMEPGAE_H
#define SPOTIFY_CLONE_HOMEPGAE_H
#include "../../Components/CardList/CardList.h"
#include "../../Components/Cards/AlbumCard/AlbumCard.h"
#include "../../Components/Cards/ArtistCard/ArtistCard.h"
#include "../../Components/Cards/SongCard/SongCard.h"
#include <QWidget>


class HomePage : public QWidget {
    Q_OBJECT

    CardList<AlbumCard, Album> *albumsList;
    CardList<ArtistCard, Artist> *artistsList;
    CardList<SongCard, Song> *songsList;

public:
    explicit HomePage(QWidget *parent = nullptr);

    void setAlbums(const QVector<Album> &);

    void setArtists(const QVector<Artist> &);

    void setSongs(const QVector<Song> &);

signals:
    void albumClicked(int albumId);

    void artistClicked(int artistId);

    void songClicked(int songId);

    void songPlayRequested(int songId);

    void songLikeRequested(int songId);
};


#endif
