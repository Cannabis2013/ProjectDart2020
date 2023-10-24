#include "dartsturnvalues.h"

DartsTurnValues::DartsTurnValues(IDartsPlayers* players, IDartsIndexes* _indexes, IDartsStatistics* statistics, IDartsFinishes* finishes, IDartsScores* scores, IDartsStatus* status)
    : _players(players)
    , _indexes(_indexes)
    , _statistics(statistics)
    , _finishes(finishes)
    , _scores(scores)
    , _status(status)
{
}

QByteArray DartsTurnValues::currentTurnInfo(){
        QJsonObject jsonObj;
        jsonObj["turnIndexes"] = turnIndex();
        jsonObj["playerScores"] = playerScores();
        jsonObj["currentPlayerName"] = _players->name();
        jsonObj["winnerFound"] = _status->isWinnerFound();
        jsonObj["winnerName"] = _players->winnerName();
        jsonObj["suggestions"] = finish();
        jsonObj["statistics"] = statistics();
        return QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
}

QJsonArray DartsTurnValues::playerScores(){
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

QJsonObject DartsTurnValues::turnIndex(){
        QJsonObject jsonObj;
        jsonObj["canUndo"] = _indexes->canUndo();
        jsonObj["canRedo"] = _indexes->canRedo();
        jsonObj["turnIndex"] = _indexes->index().turnIndex();
        return jsonObj;
}

QJsonArray DartsTurnValues::statistics(){
        QJsonArray jsonArr;
        const auto playerNames = _players->names();
        for (const auto& playerName : playerNames)
                jsonArr << _statistics->statistics(playerName).toJsonobject();
        return jsonArr;
}

QJsonObject DartsTurnValues::finish(){
        QJsonObject jsonObj;
        auto remaining = _scores->score().playerScore();
        jsonObj["finish"] = _finishes->suggestTargetRow(remaining, _indexes->index().turnIndex());
        return jsonObj;
}
