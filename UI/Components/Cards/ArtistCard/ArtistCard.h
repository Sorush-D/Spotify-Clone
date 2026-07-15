#ifndef SPOTIFY_CLONE_ARTISTCARD_H
#define SPOTIFY_CLONE_ARTISTCARD_H
#include <QLabel>
#include <QFrame>
#include "../../../../Entities/Artist/Artist.h"


class ArtistCard : public QFrame {
    Q_OBJECT
    Artist artist;

    QLabel *pictureLabel;
    QLabel *nameLabel;

    void setupUI();

    QPixmap getImage(const QByteArray &) const;

    void mousePressEvent(QMouseEvent *) override;

public:
    explicit ArtistCard(const Artist &, QWidget *parent = nullptr);

    void setArtist(const Artist &);

    Artist getArtist() const;

signals:
    void clicked(int artistId);
};


#endif
