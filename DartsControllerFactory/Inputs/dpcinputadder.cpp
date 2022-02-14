#include "dpcinputadder.h"


DCInput DPCInputAdder::add(DCInput &input, const DCPlayer &player, const DCMeta &meta) const
{
    input.playerName = player.name;
    input.score = 0;
    input.tournamentId = meta.tournamentID;
    return input;
}

int DPCInputAdder::calc(DCInput &input) const
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
