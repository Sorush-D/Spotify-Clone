#include "Song.h"
#include <utility>

Song::Song(
    const int id,
    QString t,
    const int y,
    QString g,
    QString audioPath,
    const int artistId,
    const int albumId,
    QByteArray picture
) : ID(id),
    title(std::move(t)),
    releaseYear(y),
    genre(std::move(g)),
    audioFilePath(std::move(audioPath)),
    artistID(artistId),
    albumID(albumId),
    coverPicture(std::move(picture)) {
}


bool Song::isSingle() const {
    return albumID == 0;
}


bool Song::operator==(const Song &other) const {
    return ID == other.ID;
}
