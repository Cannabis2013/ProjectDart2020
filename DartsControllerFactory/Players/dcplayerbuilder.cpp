#include "dcplayerbuilder.h"
#include <qjsonobject.h>
#include "Models/dcplayer.h"

DCPlayer DCPlayerBuilder::convert(const QJsonObject &json) const
{
    DCPlayer player;
    player.name = json.value("playerName").toString();
    player.id = QUuid::fromString(json.value("playerId").toString());
    return player;
}
