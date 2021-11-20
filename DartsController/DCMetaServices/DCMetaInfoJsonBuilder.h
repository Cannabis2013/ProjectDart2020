#ifndef DCMETAINFOJSONBUILDER_H
#define DCMETAINFOJSONBUILDER_H
#include "dcmeta.h"
#include "DartsController/DCJsonSLAs/idcmodeljsonbuilder.h"
class DCMetaInfoJsonBuilder : public IDCModelJsonBuilder<const DCMeta&>
{
public:
    virtual void setJsonValues(QJsonObject &obj, Model metaInfo) const override
    {
        obj["tournamentId"] = metaInfo.tournamentId.toString(QUuid::WithoutBraces);
        obj["currentPlayerId"] = metaInfo.currentPlayerId.toString(QUuid::WithoutBraces);
        obj["currentPlayerName"] = metaInfo.currentPlayerName;
        obj["winnerId"] = metaInfo.winnerId.toString(QUuid::WithoutBraces);
        obj["winnerName"] = metaInfo.winnerName;
    }
};
#endif // DCMETAINFOJSONBUILDER_H
