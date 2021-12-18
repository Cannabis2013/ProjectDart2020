#ifndef DCJSONBUILDER_H
#define DCJSONBUILDER_H
#include "DCJsonSLAs/AbstractDCJsonBuilder.h"
#include <qjsonarray.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "DCJsonSLAs/idcmodeljsonbuilder.h"
#include "Models/dcplayer.h"
#include "Models/dcplayerstats.h"
#include "Models/dcinput.h"
#include "Models/dcindex.h"
class DCJsonBuilder : public AbstractDCJsonBuilder
{
public:
    virtual QByteArray create(const DCMeta &metaInfo) const override;
    virtual QByteArray create(const QVector<DCPlayer> &scoreModels, const QVector<DCPlayerStats> &playerStats) const override;
    virtual QByteArray create(const DCTurnValues &turnValues, const DCMeta &metaInfo) const override;
    virtual QByteArray create(const DCInput &input, const DCTurnValues &turnValues, const DCMeta &metaInfo) const override;
    virtual QByteArray create(const DCInput &input, const DCTurnValues &turnValues, const DCIndex &indexe, const DCMeta &metaInfo) const override;
    virtual QByteArray create(const DCInput &input, const DCIndex &index, const DCMeta &metaInfo) const override;
    virtual QByteArray create(const DCInput &input, const DCMeta &metaInfo) const override;
    virtual QByteArray create(const DCIndex &index, const DCMeta &metaInfo) const override;
    virtual QByteArray create(const DCIndex &reqIndex, const DCIndex &index, const DCMeta &metaInfo) const override;
};

#endif // DCJSONBUILDER_H
