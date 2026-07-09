#include "Account.h"
#include <utility>

Account::Account(
    const int id,
    QString name,
    QString username,
    QString pass,
    QString bio,
    const Role r,
    QByteArray picture
) : ID(id),
    fullName(std::move(name)),
    userName(std::move(username)),
    password(std::move(pass)),
    biography(std::move(bio)),
    role(r),
    profilePicture(std::move(picture)) {
}
