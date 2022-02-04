#include "jsontoplayer.h"
#include <qjsonobject.h>
#include "Players/Models/playerstat.h"

JsonToPlayer::Player JsonToPlayer::create(const Json &json) const
{
    PlayerStat player;
    player.name = json.value("name").toString();
    return player;
}
