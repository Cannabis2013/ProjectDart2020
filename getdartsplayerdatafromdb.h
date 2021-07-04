#ifndef GETDARTSPLAYERDATAFROMDB_H
#define GETDARTSPLAYERDATAFROMDB_H

#include "igetdartsplayerdatafromdb.h"

class GetDartsPlayerDataFromDb : public IGetDartsPlayerDataFromDb
{
public:
    virtual const PlayerModel *playerModel(const int &index, const DbService *dbService) const override;
    virtual const PlayerModel *playerModel(const Id &id, const DbService *dbService) const override;
    virtual const String playerName(const Id &playerId, const DbService *dbService) const override;
    virtual const QVector<String> playerNames(const QVector<Id> &playerIds, const DbService *dbService) const override;
    virtual QVector<Id> playerIds(const DbService *dbService) const override;
    virtual int playersCount(const DbService *dbService) const override;
    virtual QVector<const PlayerModel *> playerModels(const QVector<int> &indexes, const DbService *dbService) const override;

private:
    QVector<Id> getPlayerIds(const QVector<const PlayerModel*> &models) const;
};

#endif // GETPLAYERDATAFROMDB_H
