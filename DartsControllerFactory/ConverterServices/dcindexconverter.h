#ifndef DCINDEXCONVERTER_H
#define DCINDEXCONVERTER_H
#include "ConverterSLAs/idcindexconverter.h"
#include "Models/dcindex.h"
#include <qbytearray.h>
#include <qjsonobject.h>
#include <qjsondocument.h>
class DCIndexConverter : public IDCIndexConverter
{
public:
    virtual ByteArray convert(const DCIndex &idx) const override
    {
        QJsonObject json;
        json["totalTurns"] = idx.totalTurns;
        json["turnIndex"] = idx.turnIndex;
        json["roundIndex"] = idx.roundIndex;
        json["playerIndex"] = idx.playerIndex;
        json["attemptIndex"] = idx.attemptIndex;
        return QJsonDocument(json).toJson();
    }
};
#endif // DARTSINDEXESBUILDER_H
