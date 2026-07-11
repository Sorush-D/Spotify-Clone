#include "AlbumRepository.h"
#include "../../Database/DatabaseManager.h"
#include <QtSql/QSqlQuery>

AlbumRepository &AlbumRepository::instance() {
    static AlbumRepository instance;
    return instance;
}


int AlbumRepository::save(Album &album) {
    QSqlQuery query(DatabaseManager::instance().database());

    if (album.getID() == 0) {
        query.prepare(R"(
            INSERT INTO Albums
            (artist_id, title, cover_photo)
            VALUES (?, ?, ?)
        )");

        query.addBindValue(album.getArtistID());
        query.addBindValue(album.getTitle());
        query.addBindValue(album.getCoverPicture());

        if (!query.exec()) return 0;

        const int id = query.lastInsertId().toInt();
        album.setID(id);

        return id;
    }

    query.prepare(R"(
        UPDATE Albums
        SET
            artist_id = ?,
            title = ?,
            cover_photo = ?
        WHERE id = ?
    )");

    query.addBindValue(album.getArtistID());
    query.addBindValue(album.getTitle());
    query.addBindValue(album.getCoverPicture());
    query.addBindValue(album.getID());

    if (!query.exec()) return 0;

    return album.getID();
}


bool AlbumRepository::remove(int id) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        DELETE FROM Albums
        WHERE id = ?;
    )");

    query.addBindValue(id);

    return query.exec();
}


std::optional<Album> AlbumRepository::search(int id) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        SELECT *
        FROM Albums
        WHERE id = ?;
    )");

    query.addBindValue(id);

    if (!query.exec() || !query.next()) return std::nullopt;

    Album album(
        query.value("id").toInt(),
        query.value("title").toString(),
        query.value("artist_id").toInt(),
        query.value("cover_photo").toByteArray()
    );

    return album;
}


QVector<Album> AlbumRepository::albums(int artistId) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        SELECT *
        FROM Albums
        WHERE artist_id = ?
        ORDER BY title;
    )");

    query.addBindValue(artistId);

    if (!query.exec()) return {};

    QVector<Album> albums;

    while (query.next()) {
        albums.append(
            Album(
                query.value("id").toInt(),
                query.value("title").toString(),
                query.value("artist_id").toInt(),
                query.value("cover_photo").toByteArray()
            )
        );
    }

    return albums;
}


QVector<Album> AlbumRepository::searchByTitle(const QString &title) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        SELECT *
        FROM Albums
        WHERE title LIKE ?;
    )");

    query.addBindValue("%" + title + "%");

    if (!query.exec()) return {};

    QVector<Album> albums;

    while (query.next()) {
        albums.append(
            Album(
                query.value("id").toInt(),
                query.value("title").toString(),
                query.value("artist_id").toInt(),
                query.value("cover_photo").toByteArray()
            )
        );
    }

    return albums;
}
