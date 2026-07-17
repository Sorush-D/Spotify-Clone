#ifndef SPOTIFY_CLONE_CREATEPLAYLISTPAGE_H
#define SPOTIFY_CLONE_CREATEPLAYLISTPAGE_H
#include <QLabel>
#include <QLineEdit>
#include <QListWidget>
#include <QPushButton>
#include <QWidget>
#include "../../../../Entities/Playlist/Playlist.h"
#include "../../../../Entities/Song/Song.h"


class CreatePlaylistPage : public QWidget {
    Q_OBJECT

    QLineEdit *titleEdit;

    QLabel *songsLabel;
    QListWidget *songsList;

    QLabel *errorLabel;

    QPushButton *createButton;
    QPushButton *cancelButton;

    void setupUI();

    void setupConnections();

    bool isValidFields();

public:
    explicit CreatePlaylistPage(QWidget *parent = nullptr);

    Playlist playlist() const;

    void setSongs(const QVector<Song> &);

    QVector<int> selectedSongIDs() const;

    void setError(const QString &);

    void clearError();

    void clearFields();

signals:
    void createRequested();

    void cancelRequested();
};


#endif
