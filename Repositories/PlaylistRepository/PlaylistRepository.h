#ifndef SPOTIFY_CLONE_PLAYLISTREPOSITORY_H
#define SPOTIFY_CLONE_PLAYLISTREPOSITORY_H
#include "../../Entities/Playlist/Playlist.h"
#include "../AbstractRepository/AbstractRepository.h"


class PlaylistRepository final : public AbstractRepository<Playlist> {
    PlaylistRepository() = default;

public:
    PlaylistRepository(const PlaylistRepository &) = delete;

    PlaylistRepository &operator=(const PlaylistRepository &) = delete;

    static PlaylistRepository &instance();

    int save(Playlist &) override;

    bool remove(int) override;

    std::optional<Playlist> search(int) override;

    bool insertSong(int, int);

    bool removeSong(int, int);

    QVector<Playlist> playlists(int);
};


#endif
