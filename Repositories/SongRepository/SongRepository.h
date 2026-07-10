#ifndef SPOTIFY_CLONE_SONGREPOSITORY_H
#define SPOTIFY_CLONE_SONGREPOSITORY_H
#include "../../Entities/Song/Song.h"
#include "../AbstractRepository/AbstractRepository.h"


class SongRepository final : public AbstractRepository<Song> {
    SongRepository() = default;

public:
    SongRepository(const SongRepository &) = delete;

    SongRepository &operator=(const SongRepository &) = delete;

    static SongRepository &instance();

    int save(Song &) override;

    bool remove(int) override;

    std::optional<Song> search(int) override;

    QVector<Song> singleSongs(int);

    QVector<Song> getByAlbum(int);

    QVector<Song> getByArtist(int);

    QVector<Song> getByPlaylist(int);

    QVector<Song> getByLikedSongs(int);
};


#endif
