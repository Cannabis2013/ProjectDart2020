#ifndef DCJSONBUILDER_H
#define DCJSONBUILDER_H
#include "DartsController/DCJsonSLAs/AbstractDCJsonBuilder.h"
#include <qjsonarray.h>
class DCJsonBuilder : public AbstractDCJsonBuilder
{

    // AbstractDCJsonBuilder interface
public:
    virtual QByteArray create(const DCMeta &metaInfo) const override;
    virtual QByteArray create(const QVector<DCScoreModel> &scoreModels, const QVector<DCPlayerStat> &playerStats) const override;
    virtual QByteArray create(const DCTurnValues &turnValues, const DCMeta &metaInfo) const override;
    virtual QByteArray create(AbstractDartsInput *input, const DCTurnValues &turnValues, const DCMeta &metaInfo) const override;
    virtual QByteArray create(AbstractDartsInput *input, const DCTurnValues &turnValues, IDartsIndex *indexe, const DCMeta &metaInfo) const override;
    virtual QByteArray create(AbstractDartsInput *input, IDartsIndex *index, const DCMeta &metaInfo) const override;
    virtual QByteArray create(AbstractDartsInput *input, const DCMeta &metaInfo) const override;
    virtual QByteArray create(IDartsIndex *index, const DCMeta &metaInfo) const override;
    virtual QByteArray create(IDartsIndex *reqIndex, IDartsIndex *index, const DCMeta &metaInfo) const override;
};

#endif // DCJSONBUILDER_H
