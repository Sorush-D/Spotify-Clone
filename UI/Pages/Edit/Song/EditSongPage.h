#ifndef SPOTIFY_CLONE_EDITSONGPAGE_H
#define SPOTIFY_CLONE_EDITSONGPAGE_H
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <QComboBox>
#include <QLabel>
#include <QWidget>
#include "../../../../Entities/Album/Album.h"
#include "../../../../Entities/Song/Song.h"


class EditSongPage : public QWidget {
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

    QPushButton *saveButton;
    QPushButton *cancelButton;

    QByteArray coverPicture;
    QString audioFilePath;

    void setupUI();

    void setupConnections();

    QPixmap getCover(const QByteArray &) const;

    bool isValidFields();

public:
    explicit EditSongPage(QWidget *parent = nullptr);

    void setSong(const Song &);

    void setAlbums(const QVector<Album> &);

    void setCoverPicture(const QByteArray &);

    void setAudioFile(const QString &);

    void setError(const QString &);

    void clearError();

signals:
    void changeCoverRequested();

    void browseAudioRequested();

    void saveRequested();

    void cancelRequested();
};


#endif
