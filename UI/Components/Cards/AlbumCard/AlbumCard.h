#ifndef SPOTIFY_CLONE_ALBUMCARD_H
#define SPOTIFY_CLONE_ALBUMCARD_H
#include <QLabel>
#include <QFrame>
#include "../../../../Entities/Album/Album.h"


class AlbumCard : public QFrame {
    Q_OBJECT
    Album album;

    QLabel *coverLabel;
    QLabel *titleLabel;
    QLabel *artistLabel;

    void setupUI();

    QPixmap getCover(const QByteArray &) const;

    void mousePressEvent(QMouseEvent *) override;

public:
    explicit AlbumCard(const Album &, QWidget *parent = nullptr);

    void setAlbum(const Album &);

    Album getAlbum() const;

signals:
    void clicked(int albumId);
};


#endif
