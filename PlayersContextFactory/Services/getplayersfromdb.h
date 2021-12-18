#ifndef GETPLAYERSFROMDB_H
#define GETPLAYERSFROMDB_H
#include "DbSLAs/igetplayerfromdb.h"
template<typename T>
class IPlayersDbContext;
class IPlayer;
class GetPlayersFromDb : public IGetPlayersFromDb<IPlayer,IPlayersDbContext<IPlayer>>
{
public:
    Player *player(const QUuid &id, const DbContext *dbContext) const override;
    Player *player(const QString &name, const DbContext *dbContext) const override;
    QVector<IPlayer*> players(const QVector<int> &indexes, const DbContext *dbContext) const override;
    Players players(const QVector<QUuid> &ids, const DbContext *dbContext) const override;
    Players players(const QVector<QString> &names, const DbContext *dbContext) const override;
private:
    IPlayer *model(const int &index, const Players &models) const;
    Player *model(const QUuid &id, const Players &models) const;
    Players convert(const Players &models) const;
};
#endif // GETPLAYERDATAFROMDB_H
