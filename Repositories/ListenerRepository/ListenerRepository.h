#ifndef SPOTIFY_CLONE_LISTENERREPOSITORY_H
#define SPOTIFY_CLONE_LISTENERREPOSITORY_H
#include "../../Entities/Listener/Listener.h"
#include "../AccountRepository/AccountRepository.h"


class ListenerRepository final : public AccountRepository<Listener> {
    ListenerRepository() = default;

public:
    ListenerRepository(const ListenerRepository &) = delete;

    ListenerRepository &operator=(const ListenerRepository &) = delete;

    static ListenerRepository &instance();

    int save(Listener &) override;

    bool remove(int) override;

    std::optional<Listener> search(int) override;

    std::optional<Listener> searchByUserName(const QString &) override;

    bool updateLiked(int, int);

    bool isLiked(int, int);
};


#endif
