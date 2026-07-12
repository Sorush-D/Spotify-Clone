#include "AuthenticationService.h"
#include "../../Repositories/ArtistRepository/ArtistRepository.h"
#include "../../Repositories/ListenerRepository/ListenerRepository.h"

AuthenticationService &AuthenticationService::instance() {
    static AuthenticationService instance;
    return instance;
}


bool AuthenticationService::login(const QString &username, const QString &password) {
    logout();

    const auto foundArtist = ArtistRepository::instance().searchByUserName(username);
    if (foundArtist.has_value() && foundArtist->getPassword() == password) {
        artist = foundArtist.value();
        listener.reset();
        return true;
    }

    const auto foundListener = ListenerRepository::instance().searchByUserName(username);
    if (foundListener.has_value() && foundListener->getPassword() == password) {
        listener = foundListener.value();
        artist.reset();
        return true;
    }

    return false;
}


bool AuthenticationService::isLoggedIn() const {
    return artist.has_value() || listener.has_value();
}


void AuthenticationService::logout() {
    artist.reset();
    listener.reset();
}


const std::optional<Artist> &AuthenticationService::currentArtist() const {
    return artist;
}


void AuthenticationService::updateCurrentArtist(const Artist &a) {
    artist = a;
    listener.reset();
}


const std::optional<Listener> &AuthenticationService::currentListener() const {
    return listener;
}


void AuthenticationService::updateCurrentListener(const Listener &l) {
    listener = l;
    artist.reset();
}


bool AuthenticationService::registerArtist(Artist &a) {
    const QString username = a.getUserName();
    if (ListenerRepository::instance().searchByUserName(username).has_value()) return false;

    a.setID(0);
    return ArtistRepository::instance().save(a) != 0;
}


bool AuthenticationService::registerListener(Listener &l) {
    const QString username = l.getUserName();
    if (ArtistRepository::instance().searchByUserName(username).has_value()) return false;

    l.setID(0);
    return ListenerRepository::instance().save(l) != 0;
}
