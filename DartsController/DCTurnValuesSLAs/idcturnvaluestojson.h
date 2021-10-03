#ifndef IDCTURNVALUESTOJSON_H
#define IDCTURNVALUESTOJSON_H

#include "DartsController/DCTurnValuesServices/dcturnvalues.h"
#include "iDCTurnValJsonKeys.h"
#include <qbytearray.h>
#include <qjsonobject.h>

class IDCTurnValuesToJson
{
public:
    virtual void setJsonValues(QJsonObject &obj, const DCContext::DCTurnValues *turnValues, const IDCTurnValJsonKeys *keys) const = 0;
};

#endif // IDCJSONVALUESBUILDER_H
