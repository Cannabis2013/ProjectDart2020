#include "dartsturninfo.h"

DartsTurnInfo::DartsTurnInfo(IDartsPlayers* players, IDartsIndexes* _indexes, IDartsFinishes* finishes, IDartsScores* scores, IDartsStatus* status, IDartsStatistics* statistics)
    : _players(players)
    , _indexes(_indexes)
    , _finishes(finishes)
    , _scores(scores)
    , _status(status)
    , _statistics(statistics)
{
}

QByteArray DartsTurnInfo::report()
{
        QJsonObject jsonObj;
        jsonObj["turnInfo"] = turnInfo();
        jsonObj["stats"] = statsInfo();
        jsonObj["winnerInfo"] = winnerInfo();
        jsonObj["scores"] = playerScores();
        jsonObj["suggestions"] = finish();
        return QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
}

QJsonArray DartsTurnInfo::playerScores()
{
        QJsonArray jsonArr;
        auto scores = _scores->scores();
        for (const auto& score : scores.playerScores())
                jsonArr << score.toJsonObject();
        return jsonArr;
}

QJsonObject DartsTurnInfo::turnInfo()
{
        QJsonObject jsonObj;
        jsonObj["currentPlayerName"] = _players->one().name();
        jsonObj["currentPlayerNumber"] = _indexes->index().playerIndex();
        jsonObj["canUndo"] = _indexes->canUndo();
        jsonObj["canRedo"] = _indexes->canRedo();
        jsonObj["playerTurn"] = _indexes->index().turnIndex();
        return jsonObj;
}

QJsonObject DartsTurnInfo::winnerInfo()
{
        QJsonObject jsonObj;
        jsonObj["winnerFound"] = _status->isWinnerFound();
        jsonObj["winnerName"] = _players->winner().name();
        jsonObj["winnerImage"] = _players->winner().winnerImageUrl();
        return jsonObj;
}

QJsonArray DartsTurnInfo::statsInfo()
{
        QJsonArray arr;
        auto names = _players->names();
        for (const auto& name : names)
                arr << _statistics->report(name);
        return arr;
}

QJsonObject DartsTurnInfo::finish()
{
        QJsonObject jsonObj;
        auto remaining = _scores->score().playerScore();
        jsonObj["targetRow"] = _finishes->suggestTargetRow(remaining, _indexes->index().turnIndex());
        return jsonObj;
}
