#ifndef DCJSONBUILDER_H
#define DCJSONBUILDER_H
#include "DartsController/DCJsonSLAs/AbstractDCJsonBuilder.h"
#include <qjsonarray.h>
class DCJsonBuilder : public AbstractDCJsonBuilder
{
public:
    QByteArray json(const DCMeta &metaInfo) const override;
    QByteArray json(const QVector<DCScoreModel> &scoreModels, const QVector<DCPlayerStat> &playerStats) const override;
    QByteArray json(const DCInput &input, const DCTurnValues &turnValues, const DCMeta &metaInfo) const override;
    QByteArray json(const DCTurnValues &turnValues, const DCMeta &metaInfo = DCMeta()) const override;
    QByteArray json(const DCInput &input, const DCTurnValues &turnValues, const DCIndex &indexes, const DCMeta &metaInfo) const override;
    QByteArray json(const DCInput &input, const DCIndex &indexes, const DCMeta &metaInfo) const override;
    QByteArray json(const DCIndex &index, const DCMeta &metaInfo) const override;
    QByteArray json(const DCIndex &regIndex, const DCIndex &inputIndex, const DCMeta &metaInfo) const override;
    virtual QByteArray json(const DCInput &input, const DCMeta &metaInfo) const override;
};

#endif // DCJSONBUILDER_H
