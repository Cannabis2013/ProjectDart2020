#ifndef ABSTRACTPLAYERMODELSCONTEXT_H
#define ABSTRACTPLAYERMODELSCONTEXT_H

#include <quuid.h>
#include "ipersistence.h"

template<typename TPlayerModel, typename TSTring, typename TUuid>
class IPlayerModelsService
{
public:
    typedef TPlayerModel PlayerModel;
    typedef TSTring String ;
    typedef TUuid Id;
    // Manipulate db methods
    virtual const Id addPlayerModelToDb(const PlayerModel* playerModel) = 0;
    virtual bool deletePlayer(const int &index) = 0;
    virtual bool deletePlayersByIndexes(const QVector<int>& indexes) = 0;
    // Retrieve data methods
    virtual const PlayerModel *playerModelByIndex(const int &index) const = 0;
    virtual Id playerIdFromIndex(const int &index) const = 0;
    virtual QList<Id> playerIds() const = 0;
    virtual int playersCount() const = 0;
    // Assemble methods
    virtual QVector<String> createPlayerNamesFromIds(const QVector<Id> &ids) const = 0;
    virtual QVector<Id> createPlayerIds(const QVector<int> &indexes) const = 0;
};


#endif // ABSTRACTPLAYERMODELSCONTEXT_H
