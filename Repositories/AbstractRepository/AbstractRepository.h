#ifndef SPOTIFY_CLONE_ABSTRACTREPOSITORY_H
#define SPOTIFY_CLONE_ABSTRACTREPOSITORY_H
#include <optional>


template<class T>
class AbstractRepository {
public:
    virtual ~AbstractRepository() = default;

    virtual int save(T &) = 0;

    virtual bool remove(int) = 0;

    virtual std::optional<T> search(int) = 0;
};


#endif
