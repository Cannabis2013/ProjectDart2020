#ifndef IDCTURNVALUESTOJSON_H
#define IDCTURNVALUESTOJSON_H

#include "dcturnvalues.h"
#include <qbytearray.h>

class IDCTurnValuesToJson
{
public:
    virtual QByteArray create(const DCContext::DCTurnValues *turnValues) const = 0;
};

#endif // IDCJSONVALUESBUILDER_H
