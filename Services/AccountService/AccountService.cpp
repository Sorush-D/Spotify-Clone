#include "AccountService.h"
#include "../../Repositories/ArtistRepository/ArtistRepository.h"
#include "../../Repositories/ListenerRepository/ListenerRepository.h"
#include "../AuthenticationService/AuthenticationService.h"

AccountService &AccountService::instance() {
    static AccountService instance;
    return instance;
}


bool AccountService::updateAccount(const Account &account) {
    auto &auth = AuthenticationService::instance();
    const auto foundArtist = ArtistRepository::instance().searchByUserName(account.getUserName());
    const auto foundListener = ListenerRepository::instance().searchByUserName(account.getUserName());

    if (auth.currentArtist().has_value()) {
        Artist artist = auth.currentArtist().value();

        if (foundListener) return false;
        if (foundArtist && foundArtist->getID() != artist.getID()) return false;

        artist.setFullName(account.getFullName());
        artist.setUserName(account.getUserName());
        artist.setPassword(account.getPassword());
        artist.setBiography(account.getBiography());
        artist.setProfilePicture(account.getProfilePicture());

        if (ArtistRepository::instance().save(artist) == 0) return false;

        auth.updateCurrentArtist(artist);
        return true;
    }

    if (auth.currentListener().has_value()) {
        Listener listener = auth.currentListener().value();

        if (foundArtist) return false;
        if (foundListener && foundListener->getID() != listener.getID()) return false;

        listener.setFullName(account.getFullName());
        listener.setUserName(account.getUserName());
        listener.setPassword(account.getPassword());
        listener.setBiography(account.getBiography());
        listener.setProfilePicture(account.getProfilePicture());

        if (ListenerRepository::instance().save(listener) == 0) return false;

        auth.updateCurrentListener(listener);
        return true;
    }

    return false;
}


bool AccountService::deleteAccount() {
    auto &auth = AuthenticationService::instance();

    bool isDeleted = false;

    if (auth.currentArtist().has_value())
        isDeleted = ArtistRepository::instance().remove(auth.currentArtist()->getID());

    else if (auth.currentListener().has_value())
        isDeleted = ListenerRepository::instance().remove(auth.currentListener()->getID());

    if (isDeleted) auth.logout();

    return isDeleted;
}


bool AccountService::changePassword(const QString &password) {
    auto &auth = AuthenticationService::instance();

    if (auth.currentArtist().has_value()) {
        Artist artist = auth.currentArtist().value();
        artist.setPassword(password);

        if (ArtistRepository::instance().save(artist) == 0) return false;

        auth.updateCurrentArtist(artist);
        return true;
    }

    if (auth.currentListener().has_value()) {
        Listener listener = auth.currentListener().value();
        listener.setPassword(password);

        if (ListenerRepository::instance().save(listener) == 0) return false;

        auth.updateCurrentListener(listener);
        return true;
    }

    return false;
}


bool AccountService::changeUsername(const QString &username) {
    auto &auth = AuthenticationService::instance();
    const auto foundArtist = ArtistRepository::instance().searchByUserName(username);
    const auto foundListener = ListenerRepository::instance().searchByUserName(username);

    if (auth.currentArtist().has_value()) {
        Artist artist = auth.currentArtist().value();

        if (foundListener) return false;
        if (foundArtist && foundArtist->getID() != artist.getID()) return false;

        artist.setUserName(username);

        if (ArtistRepository::instance().save(artist) == 0) return false;

        auth.updateCurrentArtist(artist);
        return true;
    }

    if (auth.currentListener().has_value()) {
        Listener listener = auth.currentListener().value();

        if (foundArtist) return false;
        if (foundListener && foundListener->getID() != listener.getID()) return false;

        listener.setUserName(username);

        if (ListenerRepository::instance().save(listener) == 0) return false;

        auth.updateCurrentListener(listener);
        return true;
    }

    return false;
}


bool AccountService::changeBiography(const QString &bio) {
    auto &auth = AuthenticationService::instance();

    if (auth.currentArtist().has_value()) {
        Artist artist = auth.currentArtist().value();
        artist.setBiography(bio);

        if (ArtistRepository::instance().save(artist) == 0) return false;

        auth.updateCurrentArtist(artist);
        return true;
    }

    if (auth.currentListener().has_value()) {
        Listener listener = auth.currentListener().value();
        listener.setBiography(bio);

        if (ListenerRepository::instance().save(listener) == 0) return false;

        auth.updateCurrentListener(listener);
        return true;
    }

    return false;
}


bool AccountService::changeProfilePicture(const QByteArray &picture) {
    auto &auth = AuthenticationService::instance();

    if (auth.currentArtist().has_value()) {
        Artist artist = auth.currentArtist().value();
        artist.setProfilePicture(picture);

        if (ArtistRepository::instance().save(artist) == 0) return false;

        auth.updateCurrentArtist(artist);
        return true;
    }

    if (auth.currentListener().has_value()) {
        Listener listener = auth.currentListener().value();
        listener.setProfilePicture(picture);

        if (ListenerRepository::instance().save(listener) == 0) return false;

        auth.updateCurrentListener(listener);
        return true;
    }

    return false;
}
