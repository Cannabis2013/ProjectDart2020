#include "dcconvertplayers.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "ModelBuilderSLAs/idcmodelconverter.h"
#include "Models/dcplayer.h"

DCConvertPlayers::Models DCConvertPlayers::convert(const QByteArray &byteArray, ModelBuilder *builder) const
{
    auto json = QJsonDocument::fromJson(byteArray).object();
    auto arr = json["assignedPlayerDetails"].toArray();
    Models models;
    for (const auto &jsonVal : qAsConst(arr))
        models << builder->create(jsonVal.toObject());
    return models;
}
