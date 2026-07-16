#ifndef SPOTIFY_CLONE_PROFILEEDITPAGE_H
#define SPOTIFY_CLONE_PROFILEEDITPAGE_H
#include "../../../Entities/Artist/Artist.h"
#include "../../../Entities/Listener/Listener.h"
#include <QLabel>
#include <QLineEdit>
#include <QTextEdit>
#include <QPushButton>
#include <QWidget>


class ProfileEditPage : public QWidget {
    Q_OBJECT

    QLabel *pictureLabel;

    QPushButton *changePictureButton;

    QLineEdit *fullNameEdit;
    QLineEdit *usernameEdit;

    QLineEdit *passwordEdit;
    QLineEdit *confirmPasswordEdit;

    QTextEdit *bioEdit;

    QPushButton *saveButton;
    QPushButton *cancelButton;

    QByteArray profilePicture;

    QLabel *errorLabel;

    void setupUI();

    QPixmap getProfilePicture(const QByteArray &) const;

    bool isValidPasswordFields();

public:
    explicit ProfileEditPage(QWidget *parent = nullptr);

    void setArtist(const Artist &);

    void setListener(const Listener &);

    void setError(const QString &);

    void clearError();

signals:
    void changePictureRequested();

    void saveRequested();

    void cancelRequested();
};


#endif
