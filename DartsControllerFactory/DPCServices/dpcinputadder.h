#ifndef DPCINPUTADDER_H
#define DPCINPUTADDER_H
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "Models/dcmeta.h"
#include "DCInputSLAs/idcinputadder.h"
#include "Models/dcindex.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"
class DPCInputAdder : public IDCInputAdder
{
public:
    DCInput add(DCInput &input, const DCIndex &idx, const DCPlayer &player, const DCMeta &meta) const override
    {
        input.playerName = player.name;
        input.score = calc(input);
        input.remScore = player.remScore;
        input.inGame = false;
        input.roundIndex = idx.roundIndex;
        input.playerIndex = idx.playerIndex;
        input.attemptIndex = idx.attemptIndex;
        input.tournamentId = meta.tournamentId;
        return input;
    }
    DCInput add(DCInput &input, const DCPlayer &player, const DCMeta &meta) const override
    {
        input.playerName = player.name;
        input.score = 0;
        input.inGame = true;
        input.tournamentId = meta.tournamentId;
        return input;
    }
private:
    enum PointKeyCodes{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C,
        BullModifier,
        BullsEyeModifier
    };
    int calc(DCInput &input) const
    {
        auto multiplier = createPointMultiplier(input.modKeyCode);
        return calculateScore(input.point,multiplier);
    }
    int createPointMultiplier(const int &code) const
    {
        auto pointMultiplier = code == TrippleModifier ? 3 :
                               code == DoubleModifier ? 2 :
                               code == SingleModifer ? 1 : 0;
        return pointMultiplier;
    }
    int calculateScore(const int &point, const int &multiplier) const
    {
        return point*multiplier;
    }
};
#endif // DARTSCONTROLLERPOINTBUILDER_H
