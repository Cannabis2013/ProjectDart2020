#ifndef IGETPLAYERSFROMDB_H
#define IGETPLAYERSFROMDB_H
#include <quuid.h>
#include <qvector.h>
template<typename TModel, typename TDbContext>
class IGetPlayersFromDb
{
public:
    typedef TModel Player;
    typedef QVector<Player*> Players;
    typedef TDbContext DbContext;
    virtual Player *player(const QUuid &id, const DbContext *dbContext) const = 0;
    virtual Player *player(const QString &name, const DbContext *dbContext) const = 0;
    virtual Players players(const QVector<int> &indexes, const DbContext *dbContext) const = 0;
    virtual Players players(const QVector<QUuid> &ids, const DbContext *dbContext) const = 0;
    virtual Players players(const QVector<QString> &names, const DbContext *dbContext) const = 0;
};
#endif // IGETDARTSPLAYERDATAFROMDB_H
