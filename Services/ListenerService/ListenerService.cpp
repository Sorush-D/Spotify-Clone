#include "ListenerService.h"
#include "../../Repositories/ListenerRepository/ListenerRepository.h"
#include "../../Repositories/PlaylistRepository/PlaylistRepository.h"
#include "../../Repositories/SongRepository/SongRepository.h"
#include "../AuthenticationService/AuthenticationService.h"
#include <QVector>

bool ListenerService::isLoggedInAsListener() {
    return AuthenticationService::instance().currentListener().has_value();
}


bool ListenerService::isOwnerOfPlaylist(int playlistId) {
    if (!isLoggedInAsListener()) return false;

    const auto foundPlaylist = PlaylistRepository::instance().search(playlistId);
    if (!foundPlaylist) return false;

    return foundPlaylist->getListenerID() == AuthenticationService::instance().currentListener()->getID();
}


ListenerService &ListenerService::instance() {
    static ListenerService instance;
    return instance;
}


bool ListenerService::createPlaylist(Playlist &playlist) {
    if (!isLoggedInAsListener()) return false;

    playlist.setID(0);
    playlist.setListenerID(AuthenticationService::instance().currentListener()->getID());
    return PlaylistRepository::instance().save(playlist) != 0;
}


bool ListenerService::editPlaylist(Playlist &playlist) {
    if (!isOwnerOfPlaylist(playlist.getID())) return false;

    playlist.setListenerID(AuthenticationService::instance().currentListener()->getID());
    return PlaylistRepository::instance().save(playlist) != 0;
}


bool ListenerService::deletePlaylist(int playlistId) {
    if (!isOwnerOfPlaylist(playlistId)) return false;

    return PlaylistRepository::instance().remove(playlistId);
}


bool ListenerService::addSongToPlaylist(int playlistId, int songId) {
    if (!isOwnerOfPlaylist(playlistId)) return false;

    const auto songExist = SongRepository::instance().search(songId);
    if (!songExist) return false;

    return PlaylistRepository::instance().insertSong(playlistId, songId);
}


bool ListenerService::removeSongFromPlaylist(int playlistId, int songId) {
    if (!isOwnerOfPlaylist(playlistId)) return false;

    return PlaylistRepository::instance().removeSong(playlistId, songId);
}


bool ListenerService::toggleLike(int songId) {
    if (!isLoggedInAsListener()) return false;

    const auto songExist = SongRepository::instance().search(songId);
    if (!songExist) return false;

    const int listenerId = AuthenticationService::instance().currentListener()->getID();
    return ListenerRepository::instance().updateLiked(listenerId, songId);
}


bool ListenerService::isSongLiked(int songId) {
    if (!isLoggedInAsListener()) return false;

    const auto songExist = SongRepository::instance().search(songId);
    if (!songExist) return false;

    const int listenerId = AuthenticationService::instance().currentListener()->getID();
    return ListenerRepository::instance().isLiked(listenerId, songId);
}


QVector<Playlist> ListenerService::playlists() {
    if (!isLoggedInAsListener()) return {};

    const int listenerId = AuthenticationService::instance().currentListener()->getID();
    return PlaylistRepository::instance().playlists(listenerId);
}


QVector<Song> ListenerService::favoriteSongs() {
    if (!isLoggedInAsListener()) return {};

    const int listenerId = AuthenticationService::instance().currentListener()->getID();
    return SongRepository::instance().getByLikedSongs(listenerId);
}


QVector<Song> ListenerService::playlistSongs(int playlistId) {
    if (!isOwnerOfPlaylist(playlistId)) return {};

    return SongRepository::instance().getByPlaylist(playlistId);
}
