#ifndef DCJSONBUILDER_H
#define DCJSONBUILDER_H
#include "DartsController/DCJsonSLAs/AbstractDCJsonBuilder.h"
#include <qjsonarray.h>
class DCJsonBuilder : public AbstractDCJsonBuilder
{
public:
    QByteArray json(const DCMetaInfo &metaInfo) const override;
    QByteArray json(const QVector<DCInput> &inputs) const override;
    QByteArray json(const DCInput &input, const DCTurnValues &turnValues, const DCMetaInfo &metaInfo) const override;
    QByteArray json(const DCTurnValues &turnValues, const DCMetaInfo &metaInfo = DCMetaInfo()) const override;
    QByteArray json(const DCInput &input, const DCTurnValues &turnValues, const DCIndexes &indexes,
                    const DCInputStat &stats, const DCMetaInfo &metaInfo) const override;
    QByteArray json(const DCInput &input, const DCIndexes &indexes, const DCMetaInfo &metaInfo) const override;
    QByteArray json(const DCIndexes &indexes, const DCMetaInfo &metaInfo) const override;
};

#endif // DCJSONBUILDER_H
