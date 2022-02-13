#ifndef DCMETAINFOJSONBUILDER_H
#define DCMETAINFOJSONBUILDER_H
#include "Models/dcmeta.h"
#include "DCJsonSLAs/idcmodeljsonbuilder.h"
class DCMetaInfoJsonBuilder : public IDCModelJsonBuilder<const DCMeta&>
{
public:
    virtual void setJsonValues(QJsonObject &obj, Model metaInfo) const override
    {
        obj["tournamentId"] = metaInfo.tournamentID.toString(QUuid::WithoutBraces);
        obj["currentPlayerName"] = metaInfo.playerName;
        obj["winnerName"] = metaInfo.winnerName;
        obj["initRemScore"] = metaInfo.initRemScore;
    }
};
#endif // DCMETAINFOJSONBUILDER_H
