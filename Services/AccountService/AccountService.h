#ifndef SPOTIFY_CLONE_ACCOUNTSERVICE_H
#define SPOTIFY_CLONE_ACCOUNTSERVICE_H
#include "../../Entities/Account/Account.h"

class AccountService {
    AccountService() = default;

public:
    AccountService(const AccountService &) = delete;

    AccountService &operator=(const AccountService &) = delete;

    static AccountService &instance();

    bool updateAccount(Account &);

    bool deleteAccount();

    bool changePassword(const QString &);

    bool changeUsername(const QString &);

    bool changeBiography(const QString &);

    bool changeProfilePicture(const QByteArray &);
};


#endif
