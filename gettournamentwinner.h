#ifndef GETTOURNAMENTWINNER_H
#define GETTOURNAMENTWINNER_H

#include "igettournamentwinner.h"

class GetTournamentWinner : public IGetTournamentWinner
{
    // IGetTournamentWinner interface
public:
    virtual const DartsModelsContext::IPlayerModel *getWinnerModel(const QUuid &tournamentId,
                                                                   const IGetDartsTournamentFromDb *getTournament,
                                                                   const IGetDartsPlayerModelsFromDb *getPlayerModel,
                                                                   const IDartsTournamentDb *tournamentDb,
                                                                   const IPlayerModelsDb *playersDb) const override
    {
        auto dartsTournamentModel = getTournament->tournament(tournamentId,tournamentDb);
        auto playerModel = getPlayerModel->playerModel(dartsTournamentModel->winnerId(),playersDb);
        return playerModel;
    }
};

#endif // GETTOURNAMENTWINNER_H
