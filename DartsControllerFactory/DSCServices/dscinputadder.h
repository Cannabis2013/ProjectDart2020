#ifndef DSCINPUTADDER_H
#define DSCINPUTADDER_H
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "DCInputSLAs/idcinputadder.h"
#include "Models/dcmeta.h"
#include "Models/dcindex.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"
class DSCInputAdder : public IDCInputAdder
{
public:
    DCInput add(DCInput &input, const DCIndex &idx, const DCPlayer &player, const DCMeta &meta) const override
    {
        input.playerName = player.name;
        input.playerId = player.id;
        input.remScore = player.remScore;
        input.inGame = player.in;
        input.roundIndex = idx.roundIndex;
        input.playerIndex = idx.playerIndex;
        input.attemptIndex = idx.attemptIndex;
        input.tournamentId = meta.tournamentId;
        return input;
    }
    DCInput add(DCInput &input, const int &remScore, const DCPlayer &player, const DCMeta &meta) const override
    {
        input.playerName = player.name;
        input.playerId = player.id;
        input.score = 0;
        input.remScore = remScore;
        input.inGame = true;
        input.tournamentId = meta.tournamentId;
        input.tournamentId = meta.tournamentId;
        return input;
    }
};
#endif // DARTSSCOREBUILDERSERVICE_H
