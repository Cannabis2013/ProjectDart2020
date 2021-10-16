#ifndef DCMETAJSONBUILDER_H
#define DCMETAJSONBUILDER_H

#include "DartsController/DCMetaSLAs/idcmetajsonbuilder.h"

class DCMetaJsonBuilder : public IDCMetaJsonBuilder
{
    // IDCMetaJsonBuilder interface
public:
    virtual void setValues(QJsonObject &obj, const IDCTournamentId *tournamentId, const IDCPlayerService *playerService) const override
    {
        obj["tournamentId"] = fromId(tournamentId->id());
        obj["playerId"] = fromId(playerService->currentPlayerId());
        obj["playerName"] = playerService->currentPlayerName();
    }
private:
    QString fromId(const QUuid &id) const
    {
        return id.toString(QUuid::WithoutBraces);
    }
};

#endif // DCMETAJJSONBUILDER_H
