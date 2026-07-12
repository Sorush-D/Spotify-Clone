#include "BrowseService.h"
#include <algorithm>

BrowseService &BrowseService::instance() {
    static BrowseService instance;
    return instance;
}


QVector<Song> BrowseService::sortSongs(const QVector<Song> &songs, SongSort sortBy, SortOrder order) {
    auto songsCopy = songs;

    auto compare = [sortBy, order](const Song &a, const Song &b) {
        if (sortBy == SongSort::Title)
            return order == SortOrder::Ascending ? a.getTitle() < b.getTitle() : a.getTitle() > b.getTitle();
        return order == SortOrder::Ascending
                   ? a.getReleaseYear() < b.getReleaseYear()
                   : a.getReleaseYear() > b.getReleaseYear();
    };

    std::sort(songsCopy.begin(), songsCopy.end(), compare);
    return songsCopy;
}


QVector<Album> BrowseService::sortAlbums(const QVector<Album> &albums, SortOrder order) {
    auto albumsCopy = albums;

    auto compare = [order](const Album &a, const Album &b) {
        return order == SortOrder::Ascending ? a.getTitle() < b.getTitle() : a.getTitle() > b.getTitle();
    };

    std::sort(albumsCopy.begin(), albumsCopy.end(), compare);
    return albumsCopy;
}


QVector<Playlist> BrowseService::sortPlaylists(const QVector<Playlist> &playlists, SortOrder order) {
    auto playlistsCopy = playlists;

    auto compare = [order](const Playlist &a, const Playlist &b) {
        return order == SortOrder::Ascending ? a.getTitle() < b.getTitle() : a.getTitle() > b.getTitle();
    };

    std::sort(playlistsCopy.begin(), playlistsCopy.end(), compare);
    return playlistsCopy;
}


QVector<Song> BrowseService::filterByGenre(const QVector<Song> &songs, const QString &genre) {
    QVector<Song> result;

    const auto lowerGenre = genre.toLower();
    for (const auto &song: songs) {
        if (song.getGenre().toLower() == lowerGenre)
            result.append(song);
    }

    return result;
}


QVector<Song> BrowseService::filterByReleaseYear(const QVector<Song> &songs, int year) {
    QVector<Song> result;

    for (const auto &song: songs) {
        if (song.getReleaseYear() == year)
            result.append(song);
    }

    return result;
}
