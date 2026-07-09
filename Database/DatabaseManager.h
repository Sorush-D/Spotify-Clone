#ifndef SPOTIFY_CLONE_DATABASEMANAGER_H
#define SPOTIFY_CLONE_DATABASEMANAGER_H

#include <QtSql/QSqlDatabase>


class DatabaseManager {
    QSqlDatabase db;

    DatabaseManager() = default;

public:
    DatabaseManager(const DatabaseManager &) = delete;

    DatabaseManager &operator=(const DatabaseManager &) = delete;

    static DatabaseManager &instance();

    bool open();

    void close();

    bool createTables();

    QSqlDatabase &database();

    ~DatabaseManager();
};


#endif
