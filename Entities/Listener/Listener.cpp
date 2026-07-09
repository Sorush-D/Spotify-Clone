#include "Listener.h"
#include <utility>

Listener::Listener(
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
    Role::Listener,
    std::move(picture)
) {
}


bool Listener::operator==(const Listener &other) const {
    return ID == other.ID;
}
