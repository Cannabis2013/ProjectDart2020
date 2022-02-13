#include "dcconvertplayers.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "ModelBuilderSLAs/idcjsontomodel.h"
#include "Models/dcplayer.h"

DCConvertPlayers::Models DCConvertPlayers::convert(const QByteArray &byteArray, ModelBuilder *builder) const
{
    auto json = QJsonDocument::fromJson(byteArray).object();
    auto arr = json["players"].toArray();
    Models models;
    for (const auto &jsonVal : qAsConst(arr))
        models << builder->create(jsonVal.toObject());
    return models;
}
