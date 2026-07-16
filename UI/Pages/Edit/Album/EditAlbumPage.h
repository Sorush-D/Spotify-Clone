#ifndef SPOTIFY_CLONE_EDITALBUMPAGE_H
#define SPOTIFY_CLONE_EDITALBUMPAGE_H
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QPushButton>
#include <QByteArray>
#include <QString>
#include <QWidget>
#include "../../../../Entities/Album/Album.h"


class EditAlbumPage : public QWidget {
    Q_OBJECT

    QLabel *coverLabel;
    QPushButton *changeCoverButton;

    QLineEdit *titleEdit;

    QLabel *errorLabel;

    QPushButton *saveButton;
    QPushButton *cancelButton;

    QByteArray coverPicture;

    void setupUI();

    void setupConnections();

    QPixmap getCover(const QByteArray &) const;

    bool isValidFields();

public:
    explicit EditAlbumPage(QWidget *parent = nullptr);

    void setAlbum(const Album &);

    void setCoverPicture(const QByteArray &);

    void setError(const QString &);

    void clearError();

signals:
    void changeCoverRequested();

    void saveRequested();

    void cancelRequested();
};


#endif
