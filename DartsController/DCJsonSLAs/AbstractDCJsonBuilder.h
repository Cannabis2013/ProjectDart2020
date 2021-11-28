#ifndef ABSTRACTDCJSONBUILDER_H
#define ABSTRACTDCJSONBUILDER_H
#include "dcjsonbuilderservices.h"
#include "DartsController/DCScoresServices/dcscoremodel.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
#include "DartsController/DCInputSLAs/dciptvals.h"
#include "DartsController/DCIndexSLAs/dcindex.h"
class AbstractDCJsonBuilder : public DCJsonBuilderServices
{
public:
    virtual QByteArray create(const DCMeta &metaInfo) const = 0;
    virtual QByteArray create(const QVector<DCScoreModel> &scoreModels, const QVector<DCPlayerStat> &playerStats) const = 0;
    virtual QByteArray create(const DCTurnValues &turnValues, const DCMeta &metaInfo = DCMeta()) const = 0;
    virtual QByteArray create(const DCIptVals &input, const DCTurnValues &turnValues, const DCMeta &metaInfo = DCMeta()) const = 0;
    virtual QByteArray create(const DCIptVals &input, const DCTurnValues &turnValues, const DCIndex &index, const DCMeta &metaInfo  = DCMeta()) const = 0;
    virtual QByteArray create(const DCIptVals &input, const DCIndex &index, const DCMeta &metaInfo = DCMeta()) const = 0;
    virtual QByteArray create(const DCIptVals &input, const DCMeta &metaInfo = DCMeta()) const = 0;
    virtual QByteArray create(const DCIndex &index, const DCMeta &metaInfo = DCMeta()) const = 0;
    virtual QByteArray create(const DCIndex &reqIndex, const DCIndex &index, const DCMeta &metaInfo = DCMeta()) const = 0;
};
#endif // IDCJSONBUILDER_H
