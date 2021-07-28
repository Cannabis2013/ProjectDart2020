#ifndef IGETMODELSFROMDB_H
#define IGETMODELSFROMDB_H

#include <qvector.h>

template<typename TModel, typename TUuid, typename TString, typename TDbService>
class IGetModelsFromDb
{
public:
    typedef TModel PlayerModel;
    typedef TUuid Id;
    typedef TString String;
    typedef TDbService DbService;
    virtual const PlayerModel *model(const int &index, const DbService *dbService) const = 0;
    virtual const PlayerModel *model(const Id &id, const DbService *dbService) const = 0;
    virtual QVector<const PlayerModel*> models(const QVector<int> &indexes, const DbService *dbService) const = 0;
    virtual QVector<const PlayerModel*> models(const QVector<Id> &ids, const DbService *dbService) const = 0;
};

#endif // IPLAYERDBDATARETRIEVER_H
