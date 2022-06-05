#include "dcconvertplayers.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <DartsController/Converters/idcjsontomodel.h>
#include <DartsController/Models/dcplayer.h>

DCConvertPlayers::Models DCConvertPlayers::convert(const QByteArray &byteArray, JsonToModel *jsonToPlayer) const
{
         auto json = QJsonDocument::fromJson(byteArray).object();
         auto arr = json["assignedPlayerDetails"].toArray();
         Models models;
         for (const auto &jsonVal : qAsConst(arr))
                models << jsonToPlayer->convert(jsonVal.toObject());
         return models;
}
