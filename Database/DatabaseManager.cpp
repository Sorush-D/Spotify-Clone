#include "DatabaseManager.h"
#include <QtSql/QSqlQuery>

DatabaseManager &DatabaseManager::instance() {
    static DatabaseManager instance;
    return instance;
}


bool DatabaseManager::open() {
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("spotify.db");

    return db.open();
}


void DatabaseManager::close() {
    if (db.isOpen()) {
        db.close();
    }
}


QSqlDatabase &DatabaseManager::database() {
    return db;
}


bool DatabaseManager::createTables() {
    QSqlQuery query(db);

    query.exec("PRAGMA foreign_keys = ON;");

    if (!query.exec(R"(
    CREATE TABLE IF NOT EXISTS Listeners (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        full_name TEXT NOT NULL,
        username TEXT NOT NULL UNIQUE,
        password TEXT NOT NULL,
        biography TEXT,
        profile_photo BLOB
    );
)"))
        return false;

    if (!query.exec(R"(
    CREATE TABLE IF NOT EXISTS Artists (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        full_name TEXT NOT NULL,
        username TEXT NOT NULL UNIQUE,
        password TEXT NOT NULL,
        biography TEXT,
        profile_photo BLOB
    );
)"))
        return false;

    if (!query.exec(R"(
    CREATE TABLE IF NOT EXISTS Albums (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        artist_id INTEGER NOT NULL,
        title TEXT NOT NULL,
        cover_photo BLOB,
        FOREIGN KEY (artist_id) REFERENCES Artists(id) ON DELETE CASCADE
    );
)"))
        return false;

    if (!query.exec(R"(
    CREATE TABLE IF NOT EXISTS Songs (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        artist_id INTEGER NOT NULL,
        album_id INTEGER,
        title TEXT NOT NULL,
        genre TEXT,
        release_year INTEGER,
        audio_path TEXT NOT NULL,
        cover_photo BLOB,
        FOREIGN KEY (artist_id) REFERENCES Artists(id) ON DELETE CASCADE,
        FOREIGN KEY (album_id) REFERENCES Albums(id) ON DELETE CASCADE
    );
)"))
        return false;

    if (!query.exec(R"(
    CREATE TABLE IF NOT EXISTS Playlists (
        id INTEGER PRIMARY KEY AUTOINCREMENT,
        listener_id INTEGER NOT NULL,
        title TEXT NOT NULL,
        FOREIGN KEY (listener_id) REFERENCES Listeners(id) ON DELETE CASCADE
    );
)"))
        return false;

    if (!query.exec(R"(
    CREATE TABLE IF NOT EXISTS PlaylistSongs (
        playlist_id INTEGER,
        song_id INTEGER,
        PRIMARY KEY (playlist_id, song_id),
        FOREIGN KEY (playlist_id) REFERENCES Playlists(id) ON DELETE CASCADE,
        FOREIGN KEY (song_id) REFERENCES Songs(id) ON DELETE CASCADE
    );
)"))
        return false;

    if (!query.exec(R"(
    CREATE TABLE IF NOT EXISTS LikedSongs (
        listener_id INTEGER,
        song_id INTEGER,
        PRIMARY KEY (listener_id, song_id),
        FOREIGN KEY (listener_id) REFERENCES Listeners(id) ON DELETE CASCADE,
        FOREIGN KEY (song_id) REFERENCES Songs(id) ON DELETE CASCADE
    );
)"))
        return false;

    return true;
}


DatabaseManager::~DatabaseManager() {
    close();
}
