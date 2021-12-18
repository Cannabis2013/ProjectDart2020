#ifndef ABSTRACTDCJSONBUILDER_H
#define ABSTRACTDCJSONBUILDER_H
#include "dcjsonbuilderservices.h"
template<typename T>
class QVector;
class QByteArray;
class AbstractDCJsonBuilder : public DCJsonBuilderServices
{
public:
    virtual QByteArray create(const DCMeta &metaInfo) const = 0;
    virtual QByteArray create(const QVector<DCPlayer> &scoreModels, const QVector<DCPlayerStats> &playerStats) const = 0;
    virtual QByteArray create(const DCTurnValues &turnValues, const DCMeta &metaInfo) const = 0;
    virtual QByteArray create(const DCInput &input, const DCTurnValues &turnValues, const DCMeta &metaInfo) const = 0;
    virtual QByteArray create(const DCInput &input, const DCTurnValues &turnValues, const DCIndex &index, const DCMeta &metaInfo) const = 0;
    virtual QByteArray create(const DCInput &input, const DCIndex &index, const DCMeta &metaInfo) const = 0;
    virtual QByteArray create(const DCInput &input, const DCMeta &metaInfo) const = 0;
    virtual QByteArray create(const DCIndex &index, const DCMeta &metaInfo) const = 0;
    virtual QByteArray create(const DCIndex &reqIndex, const DCIndex &index, const DCMeta &metaInfo) const = 0;
};
#endif // IDCJSONBUILDER_H
