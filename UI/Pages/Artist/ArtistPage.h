#ifndef SPOTIFY_CLONE_ARTISTPAGE_H
#define SPOTIFY_CLONE_ARTISTPAGE_H
#include "../../../Entities/Artist/Artist.h"
#include "../../Components/CardList/CardList.h"
#include "../../Components/Cards/AlbumCard/AlbumCard.h"
#include "../../Components/Cards/SongCard/SongCard.h"
#include <QLabel>
#include <QWidget>


class ArtistPage : public QWidget {
    Q_OBJECT

    QLabel *pictureLabel;

    QLabel *nameLabel;
    QLabel *bioLabel;

    CardList<AlbumCard, Album> *albumsList;
    CardList<SongCard, Song> *songsList;

    void setupUI();

    QPixmap getProfilePicture(const QByteArray &) const;

public:
    explicit ArtistPage(QWidget *parent = nullptr);

    void setArtist(const Artist &);

    void setAlbums(const QVector<Album> &);

    void setSongs(const QVector<Song> &);

signals:
    void albumClicked(int albumId);

    void songClicked(int songId);

    void songPlayRequested(int songId);

    void songLikeRequested(int songId);
};


#endif
