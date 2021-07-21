#ifndef GETTOURNAMENTWINNER_H
#define GETTOURNAMENTWINNER_H

#include "igettournamentwinner.h"
#include "itournament.h"

class GetTournamentWinner : public IGetTournamentWinner
{
    // IGetTournamentWinner interface
public:
    virtual const IModel<QUuid> *getWinnerModel(const QUuid &tournamentId,
                                                const IGetDartsTournamentFromDb *getTournament,
                                                const IGetDartsPlayerModelsFromDb *getPlayerModel,
                                                const IDbService *tournamentDb,
                                                const IDbService *playersDb) const override
    {
        auto model = getTournament->tournament(tournamentId,tournamentDb);
        auto dartsTournamentModel = dynamic_cast<const ITournament*>(model);
        auto playerModel = getPlayerModel->playerModel(dartsTournamentModel->winnerId(),playersDb);
        return playerModel;
    }
};

#endif // GETTOURNAMENTWINNER_H
