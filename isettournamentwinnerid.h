#ifndef ISETTOURNAMENTWINNERID_H
#define ISETTOURNAMENTWINNERID_H

#include <iaddplayerdetailstotournament.h>
#include <igetdartstournamentfromdb.h>

class ISetTournamentWinnerId
{
public:
    virtual void setTournamentWinner(const QUuid &tournamentId, const QUuid &winnerId,
                                     const IGetDartsTournamentFromDb *getTournament,
                                     IAddPlayerDetailsToTournament *addToTournament,
                                     IDbService *dbService) const = 0;
};
#endif // ISETTOURNAMENTWINNERID_H
