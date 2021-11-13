#ifndef ABSTRACTDCJSONBUILDER_H
#define ABSTRACTDCJSONBUILDER_H
#include "dcjsonbuilderservices.h"
#include "DartsController/DCScoresServices/dcscoremodel.h"
#include "DartsModelsContext/InputModelsSLAs/abstractdartsinput.h"
class AbstractDCJsonBuilder : public DCJsonBuilderServices
{
public:
    virtual QByteArray create(const DCMeta &metaInfo) const = 0;
    virtual QByteArray create(const QVector<DCScoreModel> &scoreModels, const QVector<DCPlayerStat> &playerStats) const = 0;
    virtual QByteArray create(const DCTurnValues &turnValues, const DCMeta &metaInfo = DCMeta()) const = 0;
    virtual QByteArray create(AbstractDartsInput *input, const DCTurnValues &turnValues, const DCMeta &metaInfo = DCMeta()) const = 0;
    virtual QByteArray create(AbstractDartsInput *input, const DCTurnValues &turnValues, IDartsIndex *indexe, const DCMeta &metaInfo  = DCMeta()) const = 0;
    virtual QByteArray create(AbstractDartsInput *input, IDartsIndex *index, const DCMeta &metaInfo = DCMeta()) const = 0;
    virtual QByteArray create(AbstractDartsInput *input, const DCMeta &metaInfo = DCMeta()) const = 0;
    virtual QByteArray create(IDartsIndex *index, const DCMeta &metaInfo = DCMeta()) const = 0;
    virtual QByteArray create(IDartsIndex *reqIndex, IDartsIndex *index, const DCMeta &metaInfo = DCMeta()) const = 0;

};
#endif // IDCJSONBUILDER_H
