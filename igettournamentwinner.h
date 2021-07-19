#ifndef IGETTOURNAMENTWINNER_H
#define IGETTOURNAMENTWINNER_H

#include "idartstournamentdb.h"
#include "iplayermodelsdb.h"
#include "igetdartstournamentfromdb.h"
#include "igetdartsplayermodelsfromdb.h"

class IGetTournamentWinner
{
public:
    virtual const DartsModelsContext::IPlayerModel *getWinnerModel(const QUuid &tournamentId,
                                                                   const IGetDartsTournamentFromDb *getTournament,
                                                                   const IGetDartsPlayerModelsFromDb *getPlayerModel,
                                                                   const IDartsTournamentDb *tournamentDb,
                                                                   const IPlayerModelsDb *playersDb) const = 0;
};

#endif // IGETTOURNAMENTWINNER_H
