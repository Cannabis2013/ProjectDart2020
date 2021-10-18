#ifndef IDCJSONBUILDER_H
#define IDCJSONBUILDER_H

#include "DartsController/DCTurnValuesServices/dcturnvalues.h"
#include "DartsController/DCMetaServices/dcmetainfo.h"
#include "DartsController/DCInputServices/dcinput.h"
#include "DartsController/DCIndexServices/dcindexes.h"

class IDCJsonBuilder
{
public:
    virtual QByteArray json(const DCMetaInfo &metaInfo) const = 0;
    virtual QByteArray json(const QVector<DCInput> &inputs) const = 0;
    virtual QByteArray json(const DCTurnValues &turnValues, const DCMetaInfo &metaInfo = DCMetaInfo()) const = 0;
    virtual QByteArray json(const DCInput &input, const DCTurnValues &turnValues, const DCMetaInfo &metaInfo = DCMetaInfo()) const = 0;
    virtual QByteArray json(const DCInput &input, const DCIndexes &indexes, const int &average, const DCMetaInfo &metaInfo  = DCMetaInfo()) const = 0;
    virtual QByteArray json(const DCInput &input, const DCIndexes &indexes, const DCMetaInfo &metaInfo = DCMetaInfo()) const = 0;
    virtual QByteArray json(const DCIndexes &indexes, const DCMetaInfo &metaInfo = DCMetaInfo()) const = 0;
};
#endif // IDCJSONBUILDER_H
