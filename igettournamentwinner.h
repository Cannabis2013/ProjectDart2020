#ifndef IGETTOURNAMENTWINNER_H
#define IGETTOURNAMENTWINNER_H

#include "idbservice.h"
#include "idbservice.h"
#include "igetdartstournamentfromdb.h"
#include "igetdartsplayermodelsfromdb.h"

class IGetTournamentWinner
{
public:
    virtual const IModel<QUuid> *getWinnerModel(const QUuid &tournamentId,
                                                const IGetDartsTournamentFromDb *getTournament,
                                                const IGetDartsPlayerModelsFromDb *getPlayerModel,
                                                const IDbService *tournamentDb,
                                                const IDbService *playersDb) const = 0;
};

#endif // IGETTOURNAMENTWINNER_H
