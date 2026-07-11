#ifndef SPOTIFY_CLONE_ARTISTREPOSITORY_H
#define SPOTIFY_CLONE_ARTISTREPOSITORY_H
#include "../../Entities/Artist/Artist.h"
#include "../AccountRepository/AccountRepository.h"


class ArtistRepository final : public AccountRepository<Artist> {
    ArtistRepository() = default;

public:
    ArtistRepository(ArtistRepository const &) = delete;

    ArtistRepository &operator=(ArtistRepository const &) = delete;

    static ArtistRepository &instance();

    int save(Artist &) override;

    bool remove(int) override;

    std::optional<Artist> search(int) override;

    std::optional<Artist> searchByUserName(const QString &) override;

    QVector<Artist> searchByName(const QString &);
};


#endif
