#include "dartsjsonreport.h"

#include "QStringList"
#include "src/DartsController/Finishes/idartsfinishes.h"
#include "src/DartsController/indexes/idartsindexes.h"
#include "src/DartsController/players/dartsplayer.h"
#include "src/DartsController/players/idartsplayers.h"
#include "src/DartsController/responses/MessageTargetRow.h"
#include "src/DartsController/scores/idartsscores.h"
#include "src/DartsController/statistics/idartsstatistics.h"
#include "src/DartsController/status/idartsstatus.h"

DartsJsonReport::DartsJsonReport(IDartsPlayers* players,
    IDartsIndexes* _indexes,
    IDartsFinishes* finishes,
    IDartsScores* scores,
    IDartsStatus* status,
    IDartsStatistics* statistics)
    : _players(players)
    , _indexes(_indexes)
    , _finishes(finishes)
    , _scores(scores)
    , _status(status)
    , _statistics(statistics)
{
}

QByteArray DartsJsonReport::report()
{
        QJsonObject jsonObj;
        jsonObj["turnInfo"] = turnInfo();
        jsonObj["statsInfo"] = statsInfo();
        jsonObj["winnerInfo"] = winnerInfo();
        jsonObj["scores"] = playerScores();
        jsonObj["messages"] = messages();
        return QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
}

QJsonArray DartsJsonReport::playerScores()
{
        QJsonArray jsonArr;
        auto scores = _scores->scores();
        for (const auto& score : scores.playerScores())
                jsonArr << score.toJsonObject();
        return jsonArr;
}

QJsonObject DartsJsonReport::turnInfo()
{
        QJsonObject jsonObj;
        jsonObj["currentPlayerName"] = _players->one().name();
        jsonObj["currentPlayerNumber"] = _indexes->index().playerIndex();
        jsonObj["canUndo"] = _indexes->canUndo();
        jsonObj["canRedo"] = _indexes->canRedo();
        jsonObj["playerTurn"] = _indexes->index().turnIndex();
        return jsonObj;
}

QJsonObject DartsJsonReport::winnerInfo()
{
        QJsonObject jsonObj;
        jsonObj["winnerFound"] = _status->isWinnerFound();
        jsonObj["winnerName"] = _players->winner().name();
        jsonObj["winnerImage"] = _players->winner().winnerImageUrl();
        return jsonObj;
}

QJsonArray DartsJsonReport::statsInfo()
{
        QJsonArray arr;
        auto names = _players->names();
        for (const auto& name : names)
                arr << _statistics->report(name);
        return arr;
}

QJsonArray DartsJsonReport::messages()
{
        QJsonArray arr;
        auto message = messageTargetRow();
        if (!message.hasRow())
                return arr;
        arr << message.jsonobject();
        return arr;
}

MessageTargetRow DartsJsonReport::messageTargetRow()
{
        auto remaining = _scores->score().playerScore();
        auto row = _finishes->suggestTargetRow(remaining, _indexes->index().turnIndex());
        return { row };
}
