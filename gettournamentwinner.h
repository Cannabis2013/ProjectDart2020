#ifndef GETTOURNAMENTWINNER_H
#define GETTOURNAMENTWINNER_H

#include "DTMCServices/igettournamentwinner.h"
#include "itournament.h"

class GetTournamentWinner : public IGetTournamentWinner
{
    // IGetTournamentWinner interface
public:
    virtual const IModel<QUuid> *getWinnerModel(const QUuid &tournamentId,
                                                const IGetDartsTournamentFromDb *getTournament,
                                                const IGetPlayersFromDb *getPlayerModel,
                                                const IModelsDbContext *tournamentDb,
                                                const IModelsDbContext *playersDb) const override
    {
        auto model = getTournament->tournament(tournamentId,tournamentDb);
        auto dartsTournamentModel = dynamic_cast<const ITournament*>(model);
        auto playerModel = getPlayerModel->model(dartsTournamentModel->winnerId(),playersDb);
        return playerModel;
    }
};

#endif // GETTOURNAMENTWINNER_H
