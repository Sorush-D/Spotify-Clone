#ifndef SPOTIFY_CLONE_EDITPLAYLISTPAGE_H
#define SPOTIFY_CLONE_EDITPLAYLISTPAGE_H
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QWidget>
#include "../../../../Entities/Playlist/Playlist.h"
#include "../../../../Entities/Song/Song.h"


class EditPlaylistPage : public QWidget {
    Q_OBJECT

    QLineEdit *titleEdit;

    QLabel *songsLabel;
    QListWidget *songsList;

    QLabel *errorLabel;

    QPushButton *saveButton;
    QPushButton *cancelButton;

    void setupUI();

    void setupConnections();

    bool isValidFields();

public:
    explicit EditPlaylistPage(QWidget *parent = nullptr);

    void setPlaylist(const Playlist &);

    void setSongs(const QVector<Song> &);

    QVector<int> selectedSongIDs() const;

    void setError(const QString &);

    void clearError();

signals:
    void saveRequested();

    void cancelRequested();
};


#endif
