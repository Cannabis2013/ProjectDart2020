#ifndef DCJSONBUILDER_H
#define DCJSONBUILDER_H
#include "DartsController/DCJsonSLAs/AbstractDCJsonBuilder.h"
#include <qjsonarray.h>
class DCJsonBuilder : public AbstractDCJsonBuilder
{
public:
    virtual QByteArray create(const DCMeta &metaInfo) const override;
    virtual QByteArray create(const QVector<DCScoreModel> &scoreModels, const QVector<DCPlayerStat> &playerStats) const override;
    virtual QByteArray create(const DCTurnValues &turnValues, const DCMeta &metaInfo) const override;
    virtual QByteArray create(const DCIptVals &input, const DCTurnValues &turnValues, const DCMeta &metaInfo) const override;
    virtual QByteArray create(const DCIptVals &input, const DCTurnValues &turnValues, const DCIndex &indexe, const DCMeta &metaInfo) const override;
    virtual QByteArray create(const DCIptVals &input, const DCIndex &index, const DCMeta &metaInfo) const override;
    virtual QByteArray create(const DCIptVals &input, const DCMeta &metaInfo) const override;
    virtual QByteArray create(const DCIndex &index, const DCMeta &metaInfo) const override;
    virtual QByteArray create(const DCIndex &reqIndex, const DCIndex &index, const DCMeta &metaInfo) const override;
};

#endif // DCJSONBUILDER_H
