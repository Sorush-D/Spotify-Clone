#ifndef SPOTIFY_CLONE_ARTIST_H
#define SPOTIFY_CLONE_ARTIST_H
#include "../Account/Account.h"


class Artist : public Account {
public:
    Artist(int, QString, QString, QString, QString, QByteArray);

    bool operator==(const Artist &) const;

    Role getRole() override;
};


#endif
