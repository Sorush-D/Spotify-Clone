#include "ListenerRepository.h"
#include "../../Database/DatabaseManager.h"
#include <QtSql/QSqlQuery>

ListenerRepository &ListenerRepository::instance() {
    static ListenerRepository instance;
    return instance;
}


int ListenerRepository::save(Listener &listener) {
    QSqlQuery query(DatabaseManager::instance().database());

    if (listener.getID() == 0) {
        query.prepare(R"(
            INSERT INTO Listeners
            (full_name, username, password, biography, profile_photo)
            VALUES (?, ?, ?, ?, ?)
        )");

        query.addBindValue(listener.getFullName());
        query.addBindValue(listener.getUserName());
        query.addBindValue(listener.getPassword());
        query.addBindValue(listener.getBiography());
        query.addBindValue(listener.getProfilePicture());

        if (!query.exec()) return 0;

        const int id = query.lastInsertId().toInt();
        listener.setID(id);

        return id;
    }

    query.prepare(R"(
        UPDATE Listeners
        SET
            full_name = ?,
            username = ?,
            password = ?,
            biography = ?,
            profile_photo = ?
        WHERE id = ?
    )");

    query.addBindValue(listener.getFullName());
    query.addBindValue(listener.getUserName());
    query.addBindValue(listener.getPassword());
    query.addBindValue(listener.getBiography());
    query.addBindValue(listener.getProfilePicture());
    query.addBindValue(listener.getID());

    if (!query.exec()) return 0;

    return listener.getID();
}


bool ListenerRepository::remove(int id) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        DELETE FROM Listeners
        WHERE id = ?;
    )");

    query.addBindValue(id);

    return query.exec();
}


std::optional<Listener> ListenerRepository::search(int id) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        SELECT *
        FROM Listeners
        WHERE id = ?;
    )");

    query.addBindValue(id);

    if (!query.exec() || !query.next()) return std::nullopt;

    Listener listener(
        query.value("id").toInt(),
        query.value("full_name").toString(),
        query.value("username").toString(),
        query.value("password").toString(),
        query.value("biography").toString(),
        query.value("profile_photo").toByteArray()
    );

    return listener;
}


std::optional<Listener> ListenerRepository::searchByUserName(const QString &username) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        SELECT *
        FROM Listeners
        WHERE username = ?;
    )");

    query.addBindValue(username);

    if (!query.exec() || !query.next()) return std::nullopt;

    Listener listener(
        query.value("id").toInt(),
        query.value("full_name").toString(),
        query.value("username").toString(),
        query.value("password").toString(),
        query.value("biography").toString(),
        query.value("profile_photo").toByteArray()
    );

    return listener;
}


bool ListenerRepository::updateLiked(int listenerId, int songId) {
    QSqlQuery query(DatabaseManager::instance().database());

    if (isLiked(listenerId, songId)) {
        query.prepare(R"(
            DELETE FROM LikedSongs
            WHERE listener_id = ? AND song_id = ?;
        )");
    } else {
        query.prepare(R"(
            INSERT INTO LikedSongs (listener_id, song_id)
            VALUES (?, ?);
        )");
    }

    query.addBindValue(listenerId);
    query.addBindValue(songId);

    return query.exec();
}


bool ListenerRepository::isLiked(int listenerId, int songId) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        SELECT 1
        FROM LikedSongs
        WHERE listener_id = ? AND song_id = ?;
    )");

    query.addBindValue(listenerId);
    query.addBindValue(songId);

    return query.exec() && query.next();
}
