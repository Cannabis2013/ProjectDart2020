#ifndef DCINDEXCONVERTER_H
#define DCINDEXCONVERTER_H
#include "Models/dcindex.h"
#include <qbytearray.h>
#include <qjsonobject.h>
#include <qjsondocument.h>
#include "DCIndexSLAs/idcindextobytearray.h"
class DCIndexConverter : public IDCIndexToByteArray
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
