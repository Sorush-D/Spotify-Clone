#ifndef SPOTIFY_CLONE_BROWSESERVICE_H
#define SPOTIFY_CLONE_BROWSESERVICE_H
#include "../../Entities/Song/Song.h"
#include "../../Entities/Album/Album.h"
#include "../../Entities/Playlist/Playlist.h"
#include <QVector>


enum class SongSort {
    Title,
    ReleaseYear
};


enum class SortOrder {
    Ascending,
    Descending
};


class BrowseService {
    BrowseService() = default;

public:
    BrowseService(BrowseService const &) = delete;

    BrowseService &operator=(BrowseService const &) = delete;

    static BrowseService &instance();

    QVector<Song> sortSongs(const QVector<Song> &songs, SongSort sortBy, SortOrder order);

    QVector<Album> sortAlbums(const QVector<Album> &albums, SortOrder order);

    QVector<Playlist> sortPlaylists(const QVector<Playlist> &playlists, SortOrder order);

    QVector<Song> filterByGenre(const QVector<Song> &songs, const QString &genre);

    QVector<Song> filterByReleaseYear(const QVector<Song> &songs, int year);
};


#endif
