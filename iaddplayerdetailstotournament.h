#ifndef IADDPLAYERDETAILSTOTOURNAMENT_H
#define IADDPLAYERDETAILSTOTOURNAMENT_H

#include "iaddplayerdetailstomodel.h"
#include "idartstournament.h"
#include "idartstournamentdb.h"

class IAddPlayerDetailsToTournament : public IAddPlayerDetailsToModel<ITournament,IDartsTournamentDb>
{
public:
    virtual void add(const ITournament *tournament,
                     const QVector<QUuid> &playerIds,
                     IDartsTournamentDb *dbService = nullptr) const override = 0;
    virtual void add(const ITournament *tournament,
                     const QVector<QString> &playerNames,
                     IDartsTournamentDb *dbService = nullptr) const override = 0;
    virtual void add(const ITournament *tournament,
                     const QUuid &winnerId,
                     IDartsTournamentDb *dbService= nullptr) const override = 0;
};

#endif // IDARTSMODELMANIPULATOR_H
