#ifndef SPOTIFY_CLONE_LISTENER_H
#define SPOTIFY_CLONE_LISTENER_H
#include "../Account/Account.h"


class Listener final : public Account {
public:
    Listener() = default;

    Listener(int, QString, QString, QString, QString, QByteArray);

    bool operator==(const Listener &) const;

    Role getRole() override;
};


#endif
