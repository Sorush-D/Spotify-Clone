#include "Artist.h"
#include <utility>

Artist::Artist(
    const int id,
    QString name,
    QString username,
    QString pass,
    QString bio,
    QByteArray picture
) : Account(
    id,
    std::move(name),
    std::move(username),
    std::move(pass),
    std::move(bio),
    Role::Artist,
    std::move(picture)
) {
}


bool Artist::operator==(const Artist &other) const {
    return ID == other.ID;
}
