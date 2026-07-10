#ifndef SPOTIFY_CLONE_SONG_H
#define SPOTIFY_CLONE_SONG_H
#include <QString>
#include <QByteArray>


class Song {
    int ID = 0;
    QString title;
    int releaseYear;
    QString genre;
    QString audioFilePath;
    int artistID;
    int albumID;
    QByteArray coverPicture;

public:
    Song() = default;

    Song(int, QString, int, QString, QString, int, int, QByteArray);

    [[nodiscard]] bool isSingle() const;

    bool operator==(const Song &other) const;

    [[nodiscard]] int getID() const { return ID; }

    void setID(const int id) { ID = id; }

    [[nodiscard]] QString getTitle() const { return title; }

    void setTitle(const QString &t) { title = t; }

    [[nodiscard]] int getReleaseYear() const { return releaseYear; }

    void setReleaseYear(const int y) { releaseYear = y; }

    [[nodiscard]] QString getGenre() const { return genre; }

    void setGenre(const QString &g) { genre = g; }

    [[nodiscard]] QString getAudioFilePath() const { return audioFilePath; }

    void setAudioFilePath(const QString &audioPath) { audioFilePath = audioPath; }

    [[nodiscard]] int getArtistID() const { return artistID; }

    void setArtistID(const int artistId) { artistID = artistId; }

    [[nodiscard]] int getAlbumID() const { return albumID; }

    void setAlbumID(const int albumId) { albumID = albumId; }

    [[nodiscard]] QByteArray getCoverPicture() const { return coverPicture; }

    void setCoverPicture(const QByteArray &picture) { coverPicture = picture; }
};


#endif
