#ifndef IDCTURNVALUESTOJSON_H
#define IDCTURNVALUESTOJSON_H

#include "DartsController/DCTurnValuesServices/dcturnvalues.h"
#include <qbytearray.h>
#include <qjsonobject.h>

class IDCTurnValuesToJson
{
public:
    virtual QJsonObject create(const DCContext::DCTurnValues *turnValues) const = 0;
};

#endif // IDCJSONVALUESBUILDER_H
