#include "dscinputadder.h"

#include <DartsController/Contracts/Models/dcinput.h>
#include <DartsController/Contracts/Models/dcmeta.h>
#include <DartsController/Contracts/Models/dcplayer.h>

DCInput DSCInputAdder::add(DCInput &input, const DCPlayer &player, const DCMeta &meta, const DCIndex &index) const
{
        input.playerName = player.name;
        input.playerId = player.id;
        input.tournamentId = meta.tournamentID;
        input.index = index;
        return input;
}
