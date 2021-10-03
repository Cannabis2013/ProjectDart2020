#ifndef IDCINDEXESTOJSON_H
#define IDCINDEXESTOJSON_H
#include <qbytearray.h>
#include <qjsonobject.h>
#include "DartsModelsContext/DMCIndexesSLAs/IDCIndexesJsonKeys.h"
#include "idcindexes.h"
class IDCIndexesToJson
{
public:
    virtual void toJson(QJsonObject &obj, const DCContext::IDCIndexes *indexes, const IDCIndexesJsonKeys *keys) const = 0;
};
#endif // IDCINDEXESTOJSON_H
