#ifndef DCMETAJSONBUILDER_H
#define DCMETAJSONBUILDER_H

#include "DartsController/DCMetaSLAs/idcmetajsonbuilder.h"

class DCMetaJsonBuilder : public IDCMetaJsonBuilder
{
public:
    virtual void setValues(QJsonObject &obj, const IDCTournamentId *tournamentId, const IDCPlayerService *playerService,
                           const IDCWinnerService *winnerService, const IDCIndexController *indexContext,
                           IDCScoresService *scoresContext) const override
    {
        obj["tournamentId"] = fromId(tournamentId->id());
        obj["playerId"] = fromId(playerService->currentPlayerId(indexContext,scoresContext));
        obj["playerName"] = playerService->currentPlayerName(indexContext,scoresContext);
        obj["winnerId"] = fromId(winnerService->winnerId());
        obj["winnerName"] = winnerService->winnerName();
    }
private:
    QString fromId(const QUuid &id) const
    {
        return id.toString(QUuid::WithoutBraces);
    }
};

#endif // DCMETAJJSONBUILDER_H
