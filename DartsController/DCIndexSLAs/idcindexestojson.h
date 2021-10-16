#ifndef IDCINDEXESTOJSON_H
#define IDCINDEXESTOJSON_H
#include <qbytearray.h>
#include <qjsonobject.h>
#include "DartsController/DCIndexSLAs/IDCIndexesJsonKeys.h"
#include "idcindexes.h"
class IDCIndexesToJson
{
public:
    virtual void setValues(QJsonObject &obj, const DCContext::IDCIndexes *indexes, const IDCIndexesJsonKeys *keys) const = 0;
};
#endif // IDCINDEXESTOJSON_H
