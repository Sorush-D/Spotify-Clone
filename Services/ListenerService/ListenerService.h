#ifndef SPOTIFY_CLONE_LISTENERSERVICE_H
#define SPOTIFY_CLONE_LISTENERSERVICE_H
#include "../../Entities/Playlist/Playlist.h"
#include "../../Entities/Song/Song.h"

class ListenerService {
    ListenerService() = default;

    bool isLoggedInAsListener();

    bool isOwnerOfPlaylist(int);

public:
    ListenerService(const ListenerService &) = delete;

    ListenerService &operator=(const ListenerService &) = delete;

    static ListenerService &instance();

    bool createPlaylist(Playlist &);

    bool editPlaylist(Playlist &);

    bool deletePlaylist(int);

    bool addSongToPlaylist(int, int);

    bool removeSongFromPlaylist(int, int);

    bool toggleLike(int);

    bool isSongLiked(int);

    QVector<Playlist> playlists();

    QVector<Song> favoriteSongs();

    QVector<Song> playlistSongs(int);
};


#endif
