#ifndef SPOTIFY_CLONE_ALBUMCARD_H
#define SPOTIFY_CLONE_ALBUMCARD_H
#include <QLabel>
#include <QFrame>
#include <QToolButton>
#include "../../../../Entities/Album/Album.h"


class AlbumCard : public QFrame {
    Q_OBJECT
    Album album;

    QLabel *coverLabel;
    QLabel *titleLabel;
    QLabel *artistLabel;

    QToolButton *editButton;
    QToolButton *deleteButton;

    void setupUI();

    void setupConnections();

    QPixmap getCover(const QByteArray &) const;

    void mousePressEvent(QMouseEvent *) override;

public:
    explicit AlbumCard(const Album &, QWidget *parent = nullptr);

    void setAlbum(const Album &);

    Album getAlbum() const;

    void hideEDButtons();

    void showEDButtons();

signals:
    void clicked(int albumId);

    void editRequested(int albumId);

    void deleteRequested(int albumId);
};


#endif
