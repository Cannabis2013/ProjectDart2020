#ifndef DCMETAJSONBUILDER_H
#define DCMETAJSONBUILDER_H

#include "DartsController/DCMetaSLAs/idcmetajsonbuilder.h"

class DCMetaJsonBuilder : public IDCMetaJsonBuilder
{
public:
    virtual void setValues(QJsonObject &obj, const DCMeta &metaInfo, const DCIndex &index, IDCScoreModels *scoresContext) const override
    {
        auto playerId = scoresContext->scores().at(index.setIndex).playerId;
        auto playerName = scoresContext->scores().at(index.setIndex).playerName;
        obj["tournamentId"] = fromId(metaInfo.tournamentId);
        obj["playerId"] = fromId(playerId);
        obj["playerName"] = playerName;
        obj["winnerId"] = fromId(metaInfo.winnerId);
        obj["winnerName"] = metaInfo.winnerName;
    }
private:
    QString fromId(const QUuid &id) const
    {
        return id.toString(QUuid::WithoutBraces);
    }
};

#endif // DCMETAJJSONBUILDER_H
