#ifndef IPLAYERDBMANIPULATOR_H
#define IPLAYERDBMANIPULATOR_H

#include <qvector.h>

template<typename TPlayerModel, typename TUuid, typename  TDbService>
class IPlayerDbManipulator
{
public:
    typedef TPlayerModel PlayerModel;
    typedef TUuid Id;
    typedef TDbService DbService;
    // Manipulate db methods
    virtual Id addPlayerModelToDb(const PlayerModel* playerModel, DbService *dbService) = 0;
    virtual bool remove(const int &index, DbService *dbService) = 0;
    virtual bool remove(const QVector<int>& indexes, DbService *dbService) = 0;
};

#endif // IPLAYERDBMANIPULATOR_H
