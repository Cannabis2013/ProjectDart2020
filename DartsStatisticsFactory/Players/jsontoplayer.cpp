#include "jsontoplayer.h"
#include <qjsonobject.h>
#include "Players/Models/currentstats.h"

JsonToPlayer::Player JsonToPlayer::create(const Json &json) const
{
    Player player;
    player.name = json.value("name").toString();
    return player;
}
