#ifndef IGETPLAYERMODELSFROMDB_H
#define IGETPLAYERMODELSFROMDB_H

#include <qvector.h>

template<typename TModel, typename TUuid, typename TString, typename TDbService>
class IGetPlayerModelsFromDb
{
public:
    typedef TModel PlayerModel;
    typedef TUuid Id;
    typedef TString String;
    typedef TDbService DbService;
    virtual const PlayerModel *playerModel(const int &index, const DbService *dbService) const = 0;
    virtual const PlayerModel *playerModel(const Id &id, const DbService *dbService) const = 0;
    virtual QVector<const PlayerModel*> playerModels(const QVector<int> &indexes, const DbService *dbService) const = 0;
    virtual QVector<const PlayerModel*> playerModels(const QVector<Id> &ids, const DbService *dbService) const = 0;
};

#endif // IPLAYERDBDATARETRIEVER_H
