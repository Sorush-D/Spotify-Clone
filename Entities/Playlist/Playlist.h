#ifndef SPOTIFY_CLONE_PLAYLIST_H
#define SPOTIFY_CLONE_PLAYLIST_H
#include <QString>


class Playlist {
    int ID = 0;
    QString title;
    int listenerID;

public:
    Playlist() = default;

    Playlist(int, QString, int);

    bool operator==(const Playlist &) const;

    [[nodiscard]] int getID() const { return ID; }

    void setID(const int id) { ID = id; }

    [[nodiscard]] QString getTitle() const { return title; }

    void setTitle(const QString &t) { title = t; }

    [[nodiscard]] int getListenerID() const { return listenerID; }

    void setListenerID(const int listenerId) { listenerID = listenerId; }
};


#endif
