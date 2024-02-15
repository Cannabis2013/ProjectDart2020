#include "dartsjsonreport.h"

#include "src/DartsController/Finishes/idartsfinishes.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/jsonReport/dartsmessagesreport.h"
#include "src/DartsController/jsonReport/dartsstatsreport.h"
#include "src/DartsController/jsonReport/dartsturnreport.h"
#include "src/DartsController/players/dartsplayer.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/scores/DartsPlayerScores.h"
#include "src/DartsController/scores/idartsscores.h"
#include "src/DartsController/status/idartsstatus.h"
#include <QJsonArray>
#include <QJsonObject>

DartsJsonReport::DartsJsonReport(IDartsPlayers* players,
    IDartsIndexes* indexes,
    IDartsFinishes* finishes,
    IDartsScores* scores,
    IDartsStatus* status,
    IDartsInputs* inputs,
    IScoresCalculator* calculator)
    : _players(players)
    , _scores(scores)
    , _status(status)
{
        _statsReport = new DartsStatsReport(inputs, _scores, indexes, calculator, players);
        _turnReport = new DartsTurnReport(players, indexes);
        _messageReport = new DartsMessagesReport(finishes, scores, indexes);
}

QByteArray DartsJsonReport::report()
{
        QJsonObject jsonObj;
        jsonObj["turnInfo"] = _turnReport->report();
        jsonObj["statsInfo"] = _statsReport->report();
        jsonObj["winnerInfo"] = winnerInfo();
        jsonObj["scores"] = _scores->scores().jsonArray();
        jsonObj["messages"] = _messageReport->report();
        return QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
}

QJsonObject DartsJsonReport::winnerInfo()
{
        QJsonObject jsonObj;
        jsonObj["winnerFound"] = _status->isWinnerFound();
        jsonObj["winnerName"] = _players->winner().name();
        jsonObj["winnerImage"] = _players->winner().winnerImageUrl();
        return jsonObj;
}
