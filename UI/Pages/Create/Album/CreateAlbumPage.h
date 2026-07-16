#ifndef SPOTIFY_CLONE_CREATEALBUMPAGE_H
#define SPOTIFY_CLONE_CREATEALBUMPAGE_H
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QPushButton>
#include <QByteArray>
#include <QString>
#include <QWidget>


class CreateAlbumPage : public QWidget {
    Q_OBJECT

    QLabel *coverLabel;
    QPushButton *changeCoverButton;

    QLineEdit *titleEdit;

    QLabel *errorLabel;

    QPushButton *createButton;
    QPushButton *cancelButton;

    QByteArray coverPicture;

    void setupUI();

    void setupConnections();

    QPixmap getCover(const QByteArray &) const;

    bool isValidFields();

public:
    explicit CreateAlbumPage(QWidget *parent = nullptr);

    void setCoverPicture(const QByteArray &);

    void setError(const QString &);

    void clearError();

signals:
    void changeCoverRequested();

    void createRequested();

    void cancelRequested();
};


#endif
