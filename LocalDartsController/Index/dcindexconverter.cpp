#include "dcindexconverter.h"

#include <qjsonobject.h>
#include <DartsController/Models/dcindex.h>

QJsonObject DCIndexConverter::convert(const DCIndex &idx) const
{
        QJsonObject json;
        json["totalTurns"] = idx.totalTurns;
        json["turnIndex"] = idx.turnIndex;
        json["roundIndex"] = idx.roundIndex;
        json["playerIndex"] = idx.playerIndex;
        json["attemptIndex"] = idx.attemptIndex;
        return json;
}

