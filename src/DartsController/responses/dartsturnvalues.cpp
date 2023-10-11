#include "dartsturnvalues.h"

DartsTurnValues::DartsTurnValues(IDartsPlayers* players, IDartsIndexes* _indexes, IDartsStatistics* statistics, IDartsFinishes* finishes, IDartsScores* scores, IDartsStatus* status)
    : _players(players)
    , _indexes(_indexes)
    , _statistics(statistics)
    , _finishes(finishes)
    , _scores(scores)
    , _status(status)
{}

QByteArray DartsTurnValues::currentTurnInfo()
{
        QJsonObject jsonObj;
        jsonObj["turnIndexes"] = turnIndex();
        jsonObj["playerScores"] = playerScores();
        jsonObj["currentPlayerName"] = _players->name();
        jsonObj["winnerFound"] = _status->status() ? true : false;
        jsonObj["suggestions"] = finish();
        jsonObj["statistics"] = statistics();
        auto jsonDoc = new QJsonDocument(jsonObj);
        return jsonDoc->toJson(QJsonDocument::Compact);
}

QJsonArray DartsTurnValues::playerScores()
{
        QJsonArray jsonArr;
        auto scores = _scores->scores();
        for (const auto& score : scores.playerScores()) {
                QJsonObject jsonObj;
                jsonObj["playerName"] = score.name();
                jsonObj["playerScore"] = score.score();
                jsonArr << jsonObj;
        }
        return jsonArr;
}

QJsonObject DartsTurnValues::turnIndex()
{
        QJsonObject jsonObj;
        jsonObj["canUndo"] = _indexes->canUndo();
        jsonObj["canRedo"] = _indexes->canRedo();
        jsonObj["throwIndex"] = _indexes->index().throwIndex();
        return jsonObj;
}

QJsonObject DartsTurnValues::statistics()
{
        QJsonObject jsonObj;
        auto stats = _statistics->statistics();
        jsonObj["average"] = stats.average;
        jsonObj["low"] = stats.low;
        jsonObj["high"] = stats.high;
        return jsonObj;
}

QJsonObject DartsTurnValues::finish()
{
        QJsonObject jsonObj;
        auto remaining = _scores->score().playerScore();
        jsonObj["finish"] = _finishes->suggestTargetRow(remaining, _indexes->index().turnIndex());
        return jsonObj;
}
