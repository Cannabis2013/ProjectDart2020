#include "dscinputadder.h"

#include <DartsController/Models/dcinput.h>
#include <DartsController/Models/dcmeta.h>
#include <DartsController/Models/dcplayer.h>

DCInput DSCInputAdder::add(DCInput &input, const DCPlayer &player, const DCMeta &meta, const DCIndex &index) const
{
        input.playerName = player.name;
        input.playerId = player.id;
        input.tournamentId = meta.tournamentID;
        input.index = index;
        return input;
}
