#ifndef IDCINDEXESTOJSON_H
#define IDCINDEXESTOJSON_H
#include <qbytearray.h>
#include <qjsonobject.h>
#include "idcindexes.h"
class IDCIndexesToJson
{
public:
    virtual QJsonObject toJson(const DCContext::IDCIndexes *indexes) const = 0;
};
#endif // IDCINDEXESTOJSON_H
