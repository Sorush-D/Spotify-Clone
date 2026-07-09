#ifndef SPOTIFY_CLONE_ALBUM_H
#define SPOTIFY_CLONE_ALBUM_H
#include <QString>
#include <QByteArray>


class Album {
    int ID;
    QString title;
    int artistID;
    QByteArray coverPicture;

public:
    Album(int, QString, int, QByteArray);

    bool operator==(const Album &) const;

    [[nodiscard]] int getID() const { return ID; }

    void setID(const int id) { ID = id; }

    [[nodiscard]] QString getTitle() const { return title; }

    void setTitle(const QString &t) { title = t; }

    [[nodiscard]] int getArtistID() const { return artistID; }

    void setArtistID(const int artistId) { artistID = artistId; }

    [[nodiscard]] QByteArray getCoverPicture() const { return coverPicture; }

    void setCoverPicture(const QByteArray &picture) { coverPicture = picture; }
};


#endif