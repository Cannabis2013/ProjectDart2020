#ifndef DCINDEXCONVERTER_H
#define DCINDEXCONVERTER_H

#include <qbytearray.h>
#include <qjsonobject.h>
#include <qjsondocument.h>
#include <DartsController/Converters/idcmodeltojson.h>

struct DCIndex;

class DCIndexConverter : public IDCModelToJson<DCIndex>
{
public:
        virtual QJsonObject convert(const DCIndex &idx) const override;
};
#endif // DARTSINDEXESBUILDER_H
