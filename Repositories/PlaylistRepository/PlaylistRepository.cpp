#include "PlaylistRepository.h"
#include "../../Database/DatabaseManager.h"
#include <QtSql/QSqlQuery>

PlaylistRepository &PlaylistRepository::instance() {
    static PlaylistRepository instance;
    return instance;
}


int PlaylistRepository::save(Playlist &playlist) {
    QSqlQuery query(DatabaseManager::instance().database());

    if (playlist.getID() == 0) {
        query.prepare(R"(
            INSERT INTO Playlists
            (listener_id, title)
            VALUES (?, ?)
        )");

        query.addBindValue(playlist.getListenerID());
        query.addBindValue(playlist.getTitle());

        if (!query.exec()) return 0;

        const int id = query.lastInsertId().toInt();
        playlist.setID(id);

        return id;
    }

    query.prepare(R"(
        UPDATE Playlists
        SET
            listener_id = ?,
            title = ?
        WHERE id = ?
    )");

    query.addBindValue(playlist.getListenerID());
    query.addBindValue(playlist.getTitle());
    query.addBindValue(playlist.getID());

    if (!query.exec()) return 0;

    return playlist.getID();
}


bool PlaylistRepository::remove(int id) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        DELETE FROM Playlists
        WHERE id = ?;
    )");

    query.addBindValue(id);

    return query.exec();
}


std::optional<Playlist> PlaylistRepository::search(int id) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        SELECT *
        FROM Playlists
        WHERE id = ?;
    )");

    query.addBindValue(id);

    if (!query.exec() || !query.next())
        return std::nullopt;

    Playlist playlist(
        query.value("id").toInt(),
        query.value("title").toString(),
        query.value("listener_id").toInt()
    );

    return playlist;
}


bool PlaylistRepository::insertSong(int playlistId, int songId) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        INSERT INTO PlaylistSongs
        (playlist_id, song_id)
        VALUES (?, ?);
    )");

    query.addBindValue(playlistId);
    query.addBindValue(songId);

    return query.exec();
}


bool PlaylistRepository::removeSong(int playlistId, int songId) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        DELETE FROM PlaylistSongs
        WHERE playlist_id = ? AND song_id = ?;
    )");

    query.addBindValue(playlistId);
    query.addBindValue(songId);

    return query.exec();
}


QVector<Playlist> PlaylistRepository::playlists(int listenerId) {
    QSqlQuery query(DatabaseManager::instance().database());

    query.prepare(R"(
        SELECT *
        FROM Playlists
        WHERE listener_id = ?
        ORDER BY title;
    )");

    query.addBindValue(listenerId);

    if (!query.exec()) return {};

    QVector<Playlist> playlists;

    while (query.next()) {
        playlists.append(
            Playlist(
                query.value("id").toInt(),
                query.value("title").toString(),
                query.value("listener_id").toInt()
            )
        );
    }

    return playlists;
}
