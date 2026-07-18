#ifndef SPOTIFY_CLONE_ALBUMPAGE_H
#define SPOTIFY_CLONE_ALBUMPAGE_H
#include "../../Components/CardGrid/CardGrid.h"
#include "../../Components/Cards/AlbumCard/AlbumCard.h"
#include "../../../Entities/Album/Album.h"
#include <QWidget>


class AlbumPage : public QWidget {
    Q_OBJECT

    CardGrid<AlbumCard, Album> *albumsGrid;

    void setupUI();

public:
    explicit AlbumPage(QWidget *parent = nullptr);

    void setAlbums(const QVector<Album> &);

    void hideEDButtons();

    void showEDButtons();

signals:
    void albumClicked(int albumId);

    void albumEditRequested(int albumId);

    void albumDeleteRequested(int albumId);
};


#endif
