#include "SearchService.h"
#include "../../Repositories/ArtistRepository/ArtistRepository.h"
#include "../../Repositories/SongRepository/SongRepository.h"
#include "../../Repositories/AlbumRepository/AlbumRepository.h"

SearchService &SearchService::instance() {
    static SearchService instance;
    return instance;
}


QVector<Artist> SearchService::searchArtists(const QString &fullName) {
    return ArtistRepository::instance().searchByName(fullName);
}


QVector<Album> SearchService::searchAlbums(const QString &title) {
    return AlbumRepository::instance().searchByTitle(title);
}


QVector<Song> SearchService::searchSongs(const QString &title) {
    return SongRepository::instance().searchByTitle(title);
}


std::optional<Artist> SearchService::artist(int artistId) {
    return ArtistRepository::instance().search(artistId);
}


std::optional<Album> SearchService::album(int albumId) {
    return AlbumRepository::instance().search(albumId);
}


std::optional<Song> SearchService::song(int songId) {
    return SongRepository::instance().search(songId);
}
