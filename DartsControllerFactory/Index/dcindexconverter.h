#ifndef DCINDEXCONVERTER_H
#define DCINDEXCONVERTER_H

#include "Models/dcindex.h"
#include <qbytearray.h>
#include <qjsonobject.h>
#include <qjsondocument.h>
#include "Converters/idcmodeltojson.h"

class DCIndexConverter : public IDCModelToJson<DCIndex>
{
public:
        virtual QJsonObject convert(const DCIndex &idx) const override;
};
#endif // DARTSINDEXESBUILDER_H
