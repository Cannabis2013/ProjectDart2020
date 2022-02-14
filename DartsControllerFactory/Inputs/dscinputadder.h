#ifndef DSCINPUTADDER_H
#define DSCINPUTADDER_H
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "Inputs/idcinputadder.h"
#include "Models/dcmeta.h"
#include "Models/dcindex.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"
class DSCInputAdder : public IDCInputAdder
{
public:
    DCInput add(DCInput &input, const DCPlayer &player, const DCMeta &meta) const override
    {
        input.playerName = player.name;
        input.playerId = player.id;
        input.tournamentId = meta.tournamentID;
        return input;
    }
};
#endif // DARTSSCOREBUILDERSERVICE_H
