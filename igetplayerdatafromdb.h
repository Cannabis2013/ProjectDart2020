#ifndef IGETPLAYERDATAFROMDB_H
#define IGETPLAYERDATAFROMDB_H

#include <qvector.h>

template<typename TModel, typename TUuid, typename TString, typename TDbService>
class IGetPlayerDataFromDb
{
public:
    typedef TModel PlayerModel;
    typedef TUuid Id;
    typedef TString String;
    typedef TDbService DbService;
    virtual const PlayerModel *playerModel(const int &index, const DbService *dbService) const = 0;
    virtual const PlayerModel *playerModel(const Id &id, const DbService *dbService) const = 0;
    virtual const String playerName(const Id &playerId, const DbService *dbService) const = 0;
    virtual const QVector<String> playerNames(const QVector<Id> &playerIds, const DbService *dbService) const = 0;
    virtual QVector<const PlayerModel*> playerModels(const QVector<int> &indexes, const DbService *dbService) const = 0;
    virtual QVector<Id> playerIds(const DbService *dbService) const = 0;
    virtual int playersCount(const DbService *dbService) const = 0;
};

#endif // IPLAYERDBDATARETRIEVER_H
