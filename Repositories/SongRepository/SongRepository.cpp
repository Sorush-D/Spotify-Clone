#include "SongRepository.h"
#include "../../Database/DatabaseManager.h"
#include <QtSql/QSqlQuery>

SongRepository &SongRepository::instance() {
    static SongRepository instance;
    return instance;
}


int SongRepository::save(Song &song) {
    QSqlQuery query(DatabaseManager::instance().database());

    if (song.getID() == 0) {
        query.prepare(R"(
            INSERT INTO Songs
            (artist_id, album_id, title, genre, release_year, audio_path, cover_photo)
            VALUES (?, ?, ?, ?, ?, ?, ?)
        )");

        query.addBindValue(song.getArtistID());

        if (song.getAlbumID() == 0)
            query.addBindValue(QVariant());
        else
            query.addBindValue(song.getAlbumID());

        query.addBindValue(song.getTitle());
        query.addBindValue(song.getGenre());
        query.addBindValue(song.getReleaseYear());
        query.addBindValue(song.getAudioFilePath());
        query.addBindValue(song.getCoverPicture());

        if (!query.exec()) return 0;

        const int id = query.lastInsertId().toInt();
        song.setID(id);

        return id;
    }

    query.prepare(R"(
        UPDATE Songs
        SET
            artist_id = ?,
            album_id = ?,
            title = ?,
            genre = ?,
            release_year = ?,
            audio_path = ?,
            cover_photo = ?
        WHERE id = ?
    )");

    query.addBindValue(song.getArtistID());

    if (song.getAlbumID() == 0)
        query.addBindValue(QVariant());
    else
        query.addBindValue(song.getAlbumID());

    query.addBindValue(song.getTitle());
    query.addBindValue(song.getGenre());
    query.addBindValue(song.getReleaseYear());
    query.addBindValue(song.getAudioFilePath());
    query.addBindValue(song.getCoverPicture());
    query.addBindValue(song.getID());

    if (!query.exec()) return 0;

    return song.getID();
}


bool SongRepository::remove(int id) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        DELETE FROM Songs
        WHERE id = ?;
    )");

    query.addBindValue(id);

    return query.exec();
}


std::optional<Song> SongRepository::search(int id) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        SELECT *
        FROM Songs
        WHERE id = ?;
    )");

    query.addBindValue(id);

    if (!query.exec() || !query.next()) return std::nullopt;

    Song song(
        query.value("id").toInt(),
        query.value("title").toString(),
        query.value("release_year").toInt(),
        query.value("genre").toString(),
        query.value("audio_path").toString(),
        query.value("artist_id").toInt(),
        query.value("album_id").toInt(),
        query.value("cover_photo").toByteArray()
    );

    return song;
}


QVector<Song> SongRepository::singleSongs(int artistId) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        SELECT *
        FROM Songs
        WHERE artist_id = ?
        AND album_id IS NULL
        ORDER BY title;
    )");

    query.addBindValue(artistId);

    if (!query.exec()) return {};

    QVector<Song> songs;

    while (query.next()) {
        songs.append(
            Song(
                query.value("id").toInt(),
                query.value("title").toString(),
                query.value("release_year").toInt(),
                query.value("genre").toString(),
                query.value("audio_path").toString(),
                query.value("artist_id").toInt(),
                query.value("album_id").toInt(),
                query.value("cover_photo").toByteArray()
            )
        );
    }

    return songs;
}


QVector<Song> SongRepository::getByAlbum(int albumId) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        SELECT *
        FROM Songs
        WHERE album_id = ?
        ORDER BY title;
    )");

    query.addBindValue(albumId);

    if (!query.exec()) return {};

    QVector<Song> songs;

    while (query.next()) {
        songs.append(
            Song(
                query.value("id").toInt(),
                query.value("title").toString(),
                query.value("release_year").toInt(),
                query.value("genre").toString(),
                query.value("audio_path").toString(),
                query.value("artist_id").toInt(),
                query.value("album_id").toInt(),
                query.value("cover_photo").toByteArray()
            )
        );
    }

    return songs;
}


QVector<Song> SongRepository::getByArtist(int artistId) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        SELECT *
        FROM Songs
        WHERE artist_id = ?
        ORDER BY title;
    )");

    query.addBindValue(artistId);

    if (!query.exec()) return {};

    QVector<Song> songs;

    while (query.next()) {
        songs.append(
            Song(
                query.value("id").toInt(),
                query.value("title").toString(),
                query.value("release_year").toInt(),
                query.value("genre").toString(),
                query.value("audio_path").toString(),
                query.value("artist_id").toInt(),
                query.value("album_id").toInt(),
                query.value("cover_photo").toByteArray()
            )
        );
    }

    return songs;
}


QVector<Song> SongRepository::getByPlaylist(int playlistId) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        SELECT Songs.*
        FROM Songs
        JOIN PlaylistSongs
            ON Songs.id = PlaylistSongs.song_id
        WHERE PlaylistSongs.playlist_id = ?
        ORDER BY Songs.title;
    )");

    query.addBindValue(playlistId);

    if (!query.exec()) return {};

    QVector<Song> songs;

    while (query.next()) {
        songs.append(
            Song(
                query.value("id").toInt(),
                query.value("title").toString(),
                query.value("release_year").toInt(),
                query.value("genre").toString(),
                query.value("audio_path").toString(),
                query.value("artist_id").toInt(),
                query.value("album_id").toInt(),
                query.value("cover_photo").toByteArray()
            )
        );
    }

    return songs;
}


QVector<Song> SongRepository::getByLikedSongs(int listenerId) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        SELECT Songs.*
        FROM Songs
        JOIN LikedSongs
            ON Songs.id = LikedSongs.song_id
        WHERE LikedSongs.listener_id = ?
        ORDER BY Songs.title;
    )");

    query.addBindValue(listenerId);

    if (!query.exec()) return {};

    QVector<Song> songs;

    while (query.next()) {
        songs.append(
            Song(
                query.value("id").toInt(),
                query.value("title").toString(),
                query.value("release_year").toInt(),
                query.value("genre").toString(),
                query.value("audio_path").toString(),
                query.value("artist_id").toInt(),
                query.value("album_id").toInt(),
                query.value("cover_photo").toByteArray()
            )
        );
    }

    return songs;
}


QVector<Song> SongRepository::searchByTitle(const QString &title) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        SELECT *
        FROM Songs
        WHERE title LIKE ?;
    )");

    query.addBindValue("%" + title + "%");

    if (!query.exec()) return {};

    QVector<Song> songs;

    while (query.next()) {
        songs.append(
            Song(
                query.value("id").toInt(),
                query.value("title").toString(),
                query.value("release_year").toInt(),
                query.value("genre").toString(),
                query.value("audio_path").toString(),
                query.value("artist_id").toInt(),
                query.value("album_id").toInt(),
                query.value("cover_photo").toByteArray()
            )
        );
    }

    return songs;
}
