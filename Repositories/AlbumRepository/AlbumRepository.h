#ifndef SPOTIFY_CLONE_ALBUMREPOSITORY_H
#define SPOTIFY_CLONE_ALBUMREPOSITORY_H
#include "../../Entities/Album/Album.h"
#include "../AbstractRepository/AbstractRepository.h"


class AlbumRepository final : public AbstractRepository<Album> {
    AlbumRepository() = default;

public:
    AlbumRepository(const AlbumRepository &) = delete;

    AlbumRepository &operator=(const AlbumRepository &) = delete;

    static AlbumRepository &instance();

    int save(Album &) override;

    bool remove(int) override;

    std::optional<Album> search(int) override;

    QVector<Album> albums(int);
};


#endif
