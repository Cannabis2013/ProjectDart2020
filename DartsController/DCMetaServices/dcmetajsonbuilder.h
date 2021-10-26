#ifndef DCMETAJSONBUILDER_H
#define DCMETAJSONBUILDER_H

#include "DartsController/DCMetaSLAs/idcmetajsonbuilder.h"

class DCMetaJsonBuilder : public IDCMetaJsonBuilder
{
public:
    virtual void setValues(QJsonObject &obj, const IDCTournamentId *tournamentId, const DCPlayer &winner,
                           const DCIndex &index, IDCScoreModels *scoresContext) const override
    {
        auto playerId = scoresContext->scores().at(index.setIndex).playerId;
        auto playerName = scoresContext->scores().at(index.setIndex).playerName;
        obj["tournamentId"] = fromId(tournamentId->id());
        obj["playerId"] = fromId(playerId);
        obj["playerName"] = playerName;
        obj["winnerId"] = fromId(winner.id);
        obj["winnerName"] = winner.name;
    }
private:
    QString fromId(const QUuid &id) const
    {
        return id.toString(QUuid::WithoutBraces);
    }
};

#endif // DCMETAJJSONBUILDER_H
