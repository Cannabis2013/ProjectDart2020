#include "dartsturnreport.h"

#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/players/dartsplayer.h"
#include "src/DartsController/players/idartsplayers.h"
#include <QJsonObject>

DartsTurnReport::DartsTurnReport(IDartsPlayers* players, IDartsIndexes* indexes)
    : _players(players)
    , _indexes(indexes)
{
}

QJsonObject DartsTurnReport::report() const
{
        QJsonObject jsonObj;
        jsonObj["currentPlayerName"] = _players->one().name();
        jsonObj["currentPlayerNumber"] = _indexes->index().playerIndex();
        jsonObj["canUndo"] = _indexes->canUndo();
        jsonObj["canRedo"] = _indexes->canRedo();
        jsonObj["playerTurn"] = _indexes->index().turnIndex();
        return jsonObj;
}
