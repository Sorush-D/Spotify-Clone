#include "Playlist.h"
#include <utility>

Playlist::Playlist(
    const int id,
    QString t,
    const int listenerId
) : ID(id),
    title(std::move(t)),
    listenerID(listenerId) {
}


bool Playlist::operator==(const Playlist &other) const {
    return ID == other.ID;
}
