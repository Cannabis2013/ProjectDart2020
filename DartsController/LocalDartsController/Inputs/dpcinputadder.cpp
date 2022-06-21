#include "dpcinputadder.h"

#include <DartsController/Contracts/Models/dcinput.h>
#include <DartsController/Contracts/Models/dcmeta.h>
#include <DartsController/Contracts/Models/dcplayer.h>

DCInput DPCInputAdder::add(DCInput &input, const DCPlayer &player, const DCMeta &meta, const DCIndex &index) const
{
        input.playerName = player.name;
        input.score = calculateScore(input);
        input.tournamentId = meta.tournamentID;
        input.index = index;
        return input;
}

int DPCInputAdder::calculateScore(DCInput &input) const
{
    auto multiplier = createPointMultiplier(input.modKeyCode);
    return calculateScore(input.point,multiplier);
}

int DPCInputAdder::createPointMultiplier(const int &code) const
{
    auto pointMultiplier = code == TrippleModifier ? 3 :
                           code == DoubleModifier ? 2 :
                           code == SingleModifer ? 1 : 0;
    return pointMultiplier;
}

int DPCInputAdder::calculateScore(const int &point, const int &multiplier) const
{
    return point*multiplier;
}
