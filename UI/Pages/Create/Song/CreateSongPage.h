#ifndef SPOTIFY_CLONE_CREATESONG_H
#define SPOTIFY_CLONE_CREATESONG_H
#include <QPushButton>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QSpinBox>
#include <QWidget>
#include "../../../../Entities/Album/Album.h"
#include "../../../../Entities/Song/Song.h"


class CreateSongPage : public QWidget {
    Q_OBJECT
    QLabel *coverLabel;

    QPushButton *changeCoverButton;

    QLineEdit *titleEdit;
    QLineEdit *genreEdit;
    QSpinBox *releaseYearSpin;
    QComboBox *albumCombo;

    QLabel *audioFileLabel;
    QPushButton *browseAudioButton;

    QLabel *errorLabel;

    QPushButton *createButton;
    QPushButton *cancelButton;

    QByteArray coverPicture;
    QString audioFilePath;

    void setupUI();

    void setupConnections();

    QPixmap getCover(const QByteArray &) const;

    bool isValidFields();

public:
    explicit CreateSongPage(QWidget *parent = nullptr);

    Song song() const;

    void setAlbums(const QVector<Album> &);

    void setCoverPicture(const QByteArray &);

    void setAudioFile(const QString &);

    void setError(const QString &);

    void clearError();

    void clearFields();

signals:
    void changeCoverRequested();

    void browseAudioRequested();

    void createRequested();

    void cancelRequested();
};


#endif
