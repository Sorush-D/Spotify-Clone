#ifndef SPOTIFY_CLONE_SEARCHPAGE_H
#define SPOTIFY_CLONE_SEARCHPAGE_H
#include "../../Components/CardList/CardList.h"
#include "../../Components/Cards/AlbumCard/AlbumCard.h"
#include "../../Components/Cards/ArtistCard/ArtistCard.h"
#include "../../Components/Cards/SongCard/SongCard.h"
#include "../../../Services/BrowseService/BrowseService.h"


class SearchPage : public QWidget {
    Q_OBJECT

    QToolButton *sortButton;
    QToolButton *filterButton;

    CardList<SongCard, Song> *songsList;
    CardList<AlbumCard, Album> *albumsList;
    CardList<ArtistCard, Artist> *artistsList;

    void setupUI();

    void setupMenus();

public:
    explicit SearchPage(QWidget *parent = nullptr);

    void setSongs(const QVector<Song> &);

    void setAlbums(const QVector<Album> &);

    void setArtists(const QVector<Artist> &);

signals:
    void sortSongsRequested(SongSort, SortOrder);

    void filterGenreRequested(const QString &);

    void filterReleaseYearRequested(int);

    void albumClicked(int albumId);

    void artistClicked(int artistId);

    void songClicked(int songId);

    void songPlayRequested(int songId);

    void songLikeRequested(int songId);
};


#endif
