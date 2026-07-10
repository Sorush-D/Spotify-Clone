#ifndef SPOTIFY_CLONE_ACCOUNTREPOSITORY_H
#define SPOTIFY_CLONE_ACCOUNTREPOSITORY_H
#include "../AbstractRepository/AbstractRepository.h"
#include <QString>


template<class T>
class AccountRepository : public AbstractRepository<T> {
public:
    virtual std::optional<T> searchByUserName(const QString &) = 0;
};


#endif
