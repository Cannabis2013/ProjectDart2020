#ifndef DARTSPLAYERMODELDBMANIPULATOR_H
#define DARTSPLAYERMODELDBMANIPULATOR_H

#include "idartsplayerdbmanipulator.h"

class DartsPlayerModelDbManipulator : public IDartsPlayerDbManipulator
{
public:
    virtual Id addPlayerModelToDb(const PlayerModel *playerModel, DbService *dbService) override;
    virtual bool remove(const int &index, DbService *dbService) override;
    virtual bool remove(const QVector<int> &indexes, DbService *dbService) override;
};

#endif // DARTSPLAYERMODELDBMANIPULATOR_H
