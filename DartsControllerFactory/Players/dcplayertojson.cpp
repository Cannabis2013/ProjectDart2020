#include "dcplayertojson.h"
#include <qjsonobject.h>
#include "Models/dcplayer.h"

QJsonObject DCPlayerToJson::convert(const DCPlayer &player) const
{
    QJsonObject json;
    json["inputPlayerName"] = player.name;
    json["remainingScore"] = player.remaining;
    return json;
}


