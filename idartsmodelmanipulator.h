#ifndef IDARTSMODELMANIPULATOR_H
#define IDARTSMODELMANIPULATOR_H

#include "itournamentmodelmanipulator.h"
#include "idartstournament.h"
#include "idartstournamentdb.h"

class IDartsModelManipulator : public ITournamentModelManipulator<ITournament,IDartsTournamentDb>
{
public:
    virtual void addPlayerIds(const ITournament *tournament,
                              const QVector<QUuid> &playerIds,
                              IDartsTournamentDb *dbService = nullptr) const override = 0;
    virtual void addPlayerNames(const ITournament *tournament,
                                const QVector<QString> &playerNames,
                                IDartsTournamentDb *dbService = nullptr) const override = 0;
    virtual void setWinnerId(const ITournament *tournament,
                             const QUuid &winnerId,
                             IDartsTournamentDb *dbService= nullptr) const override = 0;
};

#endif // IDARTSMODELMANIPULATOR_H
