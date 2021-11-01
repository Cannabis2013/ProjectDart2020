#ifndef ABSTRACTDCJSONBUILDER_H
#define ABSTRACTDCJSONBUILDER_H

#include "dcjsonbuilderservices.h"

#include "DartsController/DCScoresServices/dcscoremodel.h"

class AbstractDCJsonBuilder : public DCJsonBuilderServices
{
public:
    virtual QByteArray json(const DCMeta &metaInfo) const = 0;
    virtual QByteArray json(const QVector<DCScoreModel> &scoreModels, const QVector<DCPlayerStat> &playerStats) const = 0;
    virtual QByteArray json(const DCTurnValues &turnValues, const DCMeta &metaInfo = DCMeta()) const = 0;
    virtual QByteArray json(const DCInput &input, const DCTurnValues &turnValues, const DCMeta &metaInfo = DCMeta()) const = 0;
    virtual QByteArray json(const DCInput &input, const DCTurnValues &turnValues, const DCIndex &indexes, const DCMeta &metaInfo  = DCMeta()) const = 0;
    virtual QByteArray json(const DCInput &input, const DCIndex &index, const DCMeta &metaInfo = DCMeta()) const = 0;
    virtual QByteArray json(const DCInput &input, const DCMeta &metaInfo = DCMeta()) const = 0;
    virtual QByteArray json(const DCIndex &inputIndex, const DCMeta &metaInfo = DCMeta()) const = 0;
    virtual QByteArray json(const DCIndex &reqIndex, const DCIndex &inputIndex, const DCMeta &metaInfo = DCMeta()) const = 0;

};
#endif // IDCJSONBUILDER_H
