#ifndef IGETTOURNAMENTWINNER_H
#define IGETTOURNAMENTWINNER_H

#include "imodelsdbcontext.h"
#include "imodelsdbcontext.h"
#include "igetdartstournamentfromdb.h"
#include "igetplayerfromdb.h"

class IGetTournamentWinner
{
public:
    virtual const IModel<QUuid> *getWinnerModel(const QUuid &tournamentId,
                                                const IGetDartsTournamentFromDb *getTournament,
                                                const IGetPlayersFromDb *getPlayerModel,
                                                const IModelsDbContext *tournamentDb,
                                                const IModelsDbContext *playersDb) const = 0;
};

#endif // IGETTOURNAMENTWINNER_H
