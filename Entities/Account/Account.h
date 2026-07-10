#ifndef SPOTIFY_CLONE_ACCOUNT_H
#define SPOTIFY_CLONE_ACCOUNT_H
#include <QString>
#include <QByteArray>


enum class Role {
    Artist,
    Listener
};


class Account {
protected:
    int ID = 0;
    QString fullName;
    QString userName;
    QString password;
    QString biography;
    Role role;
    QByteArray profilePicture;

public:
    Account() = default;

    Account(int, QString, QString, QString, QString, Role, QByteArray);

    virtual ~Account() = default;

    [[nodiscard]] int getID() const { return ID; }

    void setID(const int id) { ID = id; }

    [[nodiscard]] QString getFullName() const { return fullName; }

    void setFullName(const QString &name) { fullName = name; }

    [[nodiscard]] QString getUserName() const { return userName; }

    void setUserName(const QString &username) { userName = username; }

    [[nodiscard]] QString getPassword() const { return password; }

    void setPassword(const QString &pass) { password = pass; }

    [[nodiscard]] QString getBiography() const { return biography; }

    void setBiography(const QString &bio) { biography = bio; }

    virtual Role getRole() = 0;

    void setRole(const Role r) { role = r; }

    [[nodiscard]] QByteArray getProfilePicture() const { return profilePicture; }

    void setProfilePicture(const QByteArray &picture) { profilePicture = picture; }
};


#endif
