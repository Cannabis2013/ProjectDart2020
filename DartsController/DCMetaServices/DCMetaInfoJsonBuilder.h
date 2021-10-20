#ifndef DCMETAINFOJSONBUILDER_H
#define DCMETAINFOJSONBUILDER_H

#include "dcmetainfo.h"

#include "DartsController/DCJsonSLAs/idcmodeljsonbuilder.h"

class DCMetaInfoJsonBuilder : public IDCModelJsonBuilder<DCMetaInfo>
{
public:
    virtual void json(QJsonObject &obj, const Model &metaInfo) const override
    {
        obj["tournamentId"] = metaInfo.tournamentId.toString(QUuid::WithoutBraces);
        obj["currentPlayerId"] = metaInfo.currentPlayerId.toString(QUuid::WithoutBraces);
        obj["currentPlayerName"] = metaInfo.currentPlayerName;
        obj["winnerId"] = metaInfo.winnerId.toString(QUuid::WithoutBraces);
        obj["winnerName"] = metaInfo.winnerName;
    }
};
#endif // DCMETAINFOJSONBUILDER_H
