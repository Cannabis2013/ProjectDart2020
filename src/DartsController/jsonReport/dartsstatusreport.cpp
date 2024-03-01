#include "dartsstatusreport.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/players/dartsplayer.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/status/idartsstatus.h"
#include <QJsonObject>

DartsStatusReport::DartsStatusReport(IDartsPlayers* players, IDartsIndexes* indexes, IDartsStatus* status)
    : _players(players)
    , _indexes(indexes)
    , _status(status)
{
}

QJsonObject DartsStatusReport::report() const
{
        QJsonObject jsonObj;
        jsonObj["currentPlayerName"] = _players->one().name();
        jsonObj["currentPlayerNumber"] = _indexes->index().playerIndex();
        jsonObj["canUndo"] = _indexes->canUndo();
        jsonObj["canRedo"] = _indexes->canRedo();
        jsonObj["playerTurn"] = _indexes->index().turnIndex();
        jsonObj["winnerFound"] = _status->isWinnerFound();
        jsonObj["winnerName"] = _players->winner().name();
        jsonObj["winnerImage"] = _players->winner().winnerImageUrl();
        return jsonObj;
}
