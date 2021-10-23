#ifndef DCJSONBUILDER_H
#define DCJSONBUILDER_H
#include "DartsController/DCJsonSLAs/AbstractDCJsonBuilder.h"
#include <qjsonarray.h>
class DCJsonBuilder : public AbstractDCJsonBuilder
{
public:
    QByteArray json(const DCMetaInfo &metaInfo) const override;
    QByteArray json(const QVector<DCScoreModel> &scoreModels, const QVector<DCPlayerStat> &playerStats) const override;
    QByteArray json(const DCInput &input, const DCTurnValues &turnValues, const DCMetaInfo &metaInfo) const override;
    QByteArray json(const DCTurnValues &turnValues, const DCMetaInfo &metaInfo = DCMetaInfo()) const override;
    QByteArray json(const DCInput &input, const DCTurnValues &turnValues, const DCIndex &indexes, const DCMetaInfo &metaInfo) const override;
    QByteArray json(const DCInput &input, const DCIndex &indexes, const DCMetaInfo &metaInfo) const override;
    QByteArray json(const DCIndex &indexes, const DCMetaInfo &metaInfo) const override;
    QByteArray json(const DCIndex &regIndex, const DCIndex &inputIndex, const DCMetaInfo &metaInfo) const override;
};

#endif // DCJSONBUILDER_H
