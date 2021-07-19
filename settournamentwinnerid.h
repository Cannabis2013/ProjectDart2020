#ifndef SETTOURNAMENTWINNERID_H
#define SETTOURNAMENTWINNERID_H

#include "isettournamentwinnerid.h"
class SetTournamentWinnerId : public ISetTournamentWinnerId
{
public:
    virtual void setTournamentWinner(const QUuid &tournamentId,
                                     const QUuid &winnerId,
                                     const IGetDartsTournamentFromDb *getTournament,
                                     IAddPlayerDetailsToTournament *addToTournament,
                                     IDartsTournamentDb *dbService) const override
    {
        auto dartsTournamentModel = getTournament->tournament(tournamentId,dbService);
        addToTournament->add(dartsTournamentModel,winnerId,dbService);

    }
};


#endif // SETTOURNAMENTWINNERID_H
