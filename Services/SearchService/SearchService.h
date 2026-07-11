#ifndef SPOTIFY_CLONE_SEARCHSERVICE_H
#define SPOTIFY_CLONE_SEARCHSERVICE_H
#include "../../Entities/Artist/Artist.h"
#include "../../Entities/Song/Song.h"
#include "../../Entities/Album/Album.h"
#include <QVector>
#include <optional>

class SearchService {
    SearchService() = default;

public:
    SearchService(const SearchService &) = delete;

    SearchService &operator=(const SearchService &) = delete;

    static SearchService &instance();

    QVector<Artist> searchArtists(const QString &);

    QVector<Album> searchAlbums(const QString &);

    QVector<Song> searchSongs(const QString &);

    std::optional<Artist> artist(int);

    std::optional<Album> album(int);

    std::optional<Song> song(int);
};


#endif
