#include "ArtistService.h"
#include "../../Repositories/AlbumRepository/AlbumRepository.h"
#include "../../Repositories/SongRepository/SongRepository.h"
#include "../AuthenticationService/AuthenticationService.h"
#include <QVector>

bool ArtistService::isLoggedInAsArtist() {
    return AuthenticationService::instance().currentArtist().has_value();
}


bool ArtistService::isOwnerOfAlbum(int albumId) {
    if (!isLoggedInAsArtist()) return false;

    const auto foundAlbum = AlbumRepository::instance().search(albumId);
    if (!foundAlbum) return false;

    return foundAlbum->getArtistID() == AuthenticationService::instance().currentArtist()->getID();
}


bool ArtistService::isOwnerOfSong(int songId) {
    if (!isLoggedInAsArtist()) return false;

    const auto foundSong = SongRepository::instance().search(songId);
    if (!foundSong) return false;

    return foundSong->getArtistID() == AuthenticationService::instance().currentArtist()->getID();
}


ArtistService &ArtistService::instance() {
    static ArtistService instance;
    return instance;
}


bool ArtistService::createAlbum(Album &album) {
    if (!isLoggedInAsArtist()) return false;

    album.setID(0);
    album.setArtistID(AuthenticationService::instance().currentArtist()->getID());
    return AlbumRepository::instance().save(album) != 0;
}


bool ArtistService::editAlbum(Album &album) {
    if (!isOwnerOfAlbum(album.getID())) return false;

    album.setArtistID(AuthenticationService::instance().currentArtist()->getID());
    return AlbumRepository::instance().save(album) != 0;
}


bool ArtistService::deleteAlbum(int albumId) {
    if (!isOwnerOfAlbum(albumId)) return false;

    return AlbumRepository::instance().remove(albumId);
}


bool ArtistService::createSong(Song &song) {
    if (!isLoggedInAsArtist()) return false;
    if (!song.isSingle() && !isOwnerOfAlbum(song.getAlbumID())) return false;

    song.setID(0);
    song.setArtistID(AuthenticationService::instance().currentArtist()->getID());
    return SongRepository::instance().save(song) != 0;
}


bool ArtistService::editSong(Song &song) {
    if (!isOwnerOfSong(song.getID())) return false;
    if (!song.isSingle() && !isOwnerOfAlbum(song.getAlbumID())) return false;

    song.setArtistID(AuthenticationService::instance().currentArtist()->getID());
    return SongRepository::instance().save(song) != 0;
}


bool ArtistService::deleteSong(int songId) {
    if (!isOwnerOfSong(songId)) return false;

    return SongRepository::instance().remove(songId);
}


bool ArtistService::addSongToAlbum(int songId, int albumId) {
    if (!isOwnerOfSong(songId)) return false;
    if (!isOwnerOfAlbum(albumId)) return false;

    auto song = SongRepository::instance().search(songId);
    if (!song.has_value()) return false;

    song->setAlbumID(albumId);
    return SongRepository::instance().save(song.value()) != 0;
}


bool ArtistService::removeSongFromAlbum(int songId) {
    if (!isOwnerOfSong(songId)) return false;

    auto song = SongRepository::instance().search(songId);
    if (!song.has_value()) return false;

    song->setAlbumID(0);
    return SongRepository::instance().save(song.value()) != 0;
}


QVector<Album> ArtistService::myAlbums() {
    if (!isLoggedInAsArtist()) return {};

    const int artistId = AuthenticationService::instance().currentArtist()->getID();
    return AlbumRepository::instance().albums(artistId);
}


QVector<Song> ArtistService::mySongs() {
    if (!isLoggedInAsArtist()) return {};

    const int artistId = AuthenticationService::instance().currentArtist()->getID();
    return SongRepository::instance().getByArtist(artistId);
}


QVector<Song> ArtistService::mySingleSongs() {
    if (!isLoggedInAsArtist()) return {};

    const int artistId = AuthenticationService::instance().currentArtist()->getID();
    return SongRepository::instance().singleSongs(artistId);
}


QVector<Album> ArtistService::albums(int artistId) {
    return AlbumRepository::instance().albums(artistId);
}


QVector<Song> ArtistService::songs(int artistId) {
    return SongRepository::instance().getByArtist(artistId);
}


QVector<Song> ArtistService::singleSongs(int artistId) {
    return SongRepository::instance().singleSongs(artistId);
}


QVector<Song> ArtistService::albumSongs(int albumId) {
    return SongRepository::instance().getByAlbum(albumId);
}
