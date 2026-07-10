#include "ArtistRepository.h"
#include "../../Database/DatabaseManager.h"
#include <QtSql/QSqlQuery>

ArtistRepository &ArtistRepository::instance() {
    static ArtistRepository instance;
    return instance;
}


int ArtistRepository::save(Artist &artist) {
    QSqlQuery query(DatabaseManager::instance().database());

    if (artist.getID() == 0) {
        query.prepare(R"(
            INSERT INTO Artists
            (full_name, username, password, biography, profile_photo)
            VALUES (?, ?, ?, ?, ?)
        )");

        query.addBindValue(artist.getFullName());
        query.addBindValue(artist.getUserName());
        query.addBindValue(artist.getPassword());
        query.addBindValue(artist.getBiography());
        query.addBindValue(artist.getProfilePicture());

        if (!query.exec()) return 0;

        const int id = query.lastInsertId().toInt();
        artist.setID(id);

        return id;
    }

    query.prepare(R"(
        UPDATE Artists
        SET
            full_name = ?,
            username = ?,
            password = ?,
            biography = ?,
            profile_photo = ?
        WHERE id = ?
    )");

    query.addBindValue(artist.getFullName());
    query.addBindValue(artist.getUserName());
    query.addBindValue(artist.getPassword());
    query.addBindValue(artist.getBiography());
    query.addBindValue(artist.getProfilePicture());
    query.addBindValue(artist.getID());

    if (!query.exec()) return 0;

    return artist.getID();
}


bool ArtistRepository::remove(int id) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        DELETE FROM Artists
        WHERE id = ?;
    )");

    query.addBindValue(id);

    return query.exec();
}


std::optional<Artist> ArtistRepository::search(int id) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        SELECT *
        FROM Artists
        WHERE id = ?;
    )");

    query.addBindValue(id);

    if (!query.exec() || !query.next()) return std::nullopt;

    Artist artist(
        query.value("id").toInt(),
        query.value("full_name").toString(),
        query.value("username").toString(),
        query.value("password").toString(),
        query.value("biography").toString(),
        query.value("profile_photo").toByteArray()
    );

    return artist;
}


std::optional<Artist> ArtistRepository::searchByUserName(const QString &username) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        SELECT *
        FROM Artists
        WHERE username = ?;
    )");

    query.addBindValue(username);

    if (!query.exec() || !query.next()) return std::nullopt;

    Artist artist(
        query.value("id").toInt(),
        query.value("full_name").toString(),
        query.value("username").toString(),
        query.value("password").toString(),
        query.value("biography").toString(),
        query.value("profile_photo").toByteArray()
    );

    return artist;
}
