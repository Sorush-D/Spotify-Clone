#ifndef SPOTIFY_CLONE_ARTISTSERVICE_H
#define SPOTIFY_CLONE_ARTISTSERVICE_H
#include "../../Entities/Album/Album.h"
#include "../../Entities/Song/Song.h"

class ArtistService {
    ArtistService() = default;

    bool isLoggedInAsArtist();

    bool isOwnerOfAlbum(int);

    bool isOwnerOfSong(int);

public:
    ArtistService(const ArtistService &) = delete;

    ArtistService &operator=(const ArtistService &) = delete;

    static ArtistService &instance();

    bool createAlbum(Album &);

    bool editAlbum(Album &);

    bool deleteAlbum(int);

    bool createSong(Song &);

    bool editSong(Song &);

    bool deleteSong(int);

    bool addSongToAlbum(int, int);

    bool removeSongFromAlbum(int);

    QVector<Album> albums(int);

    QVector<Song> songs(int);

    QVector<Song> singleSongs(int);
};


#endif
