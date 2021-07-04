#include "dartsplayermodeldbmanipulator.h"

DartsPlayerModelDbManipulator::Id DartsPlayerModelDbManipulator::addPlayerModelToDb(const PlayerModel *playerModel, DbService *dbService)
{
    dbService->add(playerModel);
    return playerModel->id();
}

bool DartsPlayerModelDbManipulator::remove(const int &index, DbService *dbService)
{
    auto r = dbService->remove(index);
    return r;
}

bool DartsPlayerModelDbManipulator::remove(const QVector<int> &indexes, DbService *dbService)
{
    auto r = true;
    for (auto i = indexes.end(); i != indexes.begin(); --i)
        r = dbService->remove(*i) ? r : false;
    return r;
}
