#ifndef ABSTRACTDCJSONBUILDER_H
#define ABSTRACTDCJSONBUILDER_H

#include "dcjsonbuilderservices.h"

#include "DartsController/DCScoresServices/dcscoremodel.h"

class AbstractDCJsonBuilder : public DCJsonBuilderServices
{
public:
    virtual QByteArray json(const DCMetaInfo &metaInfo) const = 0;
    virtual QByteArray json(const QVector<DCScoreModel> &scoreModels, const QVector<DCPlayerStat> &playerStats) const = 0;
    virtual QByteArray json(const DCTurnValues &turnValues, const DCMetaInfo &metaInfo = DCMetaInfo()) const = 0;
    virtual QByteArray json(const DCInput &input, const DCTurnValues &turnValues, const DCMetaInfo &metaInfo = DCMetaInfo()) const = 0;
    virtual QByteArray json(const DCInput &input, const DCTurnValues &turnValues, const DCIndex &indexes, const DCMetaInfo &metaInfo  = DCMetaInfo()) const = 0;
    virtual QByteArray json(const DCInput &input, const DCIndex &indexes, const DCMetaInfo &metaInfo = DCMetaInfo()) const = 0;
    virtual QByteArray json(const DCIndex &inputIndex, const DCMetaInfo &metaInfo = DCMetaInfo()) const = 0;
    virtual QByteArray json(const DCIndex &reqIndex, const DCIndex &inputIndex, const DCMetaInfo &metaInfo = DCMetaInfo()) const = 0;

};
#endif // IDCJSONBUILDER_H
