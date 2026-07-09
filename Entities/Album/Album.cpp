#include "Album.h"
#include <utility>

Album::Album(
    const int id,
    QString t,
    const int artistId,
    QByteArray picture
) : ID(id),
    title(std::move(t)),
    artistID(artistId),
    coverPicture(std::move(picture)) {
}


bool Album::operator==(const Album &other) const {
    return ID == other.ID;
}
