#ifndef IDCINDEXESTOJSON_H
#define IDCINDEXESTOJSON_H

#include <qbytearray.h>
#include "idcindexes.h"
class IDCIndexesToJson
{
public:
    virtual QByteArray toJson(const DCContext::IDCIndexes *indexes) const = 0;
};

#endif // IDCINDEXESTOJSON_H
