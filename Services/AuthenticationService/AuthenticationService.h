#ifndef SPOTIFY_CLONE_AUTHENTICATIONSERVICE_H
#define SPOTIFY_CLONE_AUTHENTICATIONSERVICE_H
#include "../../Entities/Artist/Artist.h"
#include "../../Entities/Listener/Listener.h"
#include <optional>

class AuthenticationService {
    std::optional<Artist> artist;
    std::optional<Listener> listener;

    AuthenticationService() = default;

public:
    AuthenticationService(const AuthenticationService &) = delete;

    AuthenticationService &operator=(const AuthenticationService &) = delete;

    static AuthenticationService &instance();

    bool login(const QString &, const QString &);

    [[nodiscard]] bool isLoggedIn() const;

    void logout();

    [[nodiscard]] const std::optional<Artist> &currentArtist() const;

    [[nodiscard]] const std::optional<Listener> &currentListener() const;

    bool registerArtist(Artist &);

    bool registerListener(Listener &);
};


#endif
