#ifndef DCMETAMODELBUILDER_H
#define DCMETAMODELBUILDER_H
#include "DartsController/DCMetaSLAs/idcmetamodelbuilder.h"
class DCMetaModelBuilder : public IDCMetaModelBuilder
{
public:
    virtual DCMeta create(IDCMetaInfo *metaInfo, IDartsIndex* index, IDCScoreModels *scoreModels) const override
    {
        auto meta = metaInfo->get();
        meta.currentPlayerId = scoreModels->scores().at(index->setIndex()).playerId;
        meta.currentPlayerName = scoreModels->scores().at(index->setIndex()).playerName;
        return meta;
    }
};

#endif // DCMETAMODELBUILDER_H
