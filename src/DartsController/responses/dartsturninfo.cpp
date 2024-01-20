#include "dartsturninfo.h"

DartsTurnInfo::DartsTurnInfo(IDartsPlayers* players, IDartsIndexes* _indexes, IDartsFinishes* finishes, IDartsScores* scores, IDartsStatus* status)
    : _players(players)
    , _indexes(_indexes)
    , _finishes(finishes)
    , _scores(scores)
    , _status(status)
{
}

QByteArray DartsTurnInfo::report()
{
        QJsonObject jsonObj;
        jsonObj["turnIndexes"] = turnIndex();
        jsonObj["playerScores"] = playerScores();
        jsonObj["currentPlayerName"] = _players->player().name();
        jsonObj["winnerFound"] = _status->isWinnerFound();
        jsonObj["winnerName"] = _players->winner().name();
        jsonObj["winnerImage"] = _players->winner().winnerImageUrl();
        jsonObj["suggestions"] = finish();
        return QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
}

QJsonArray DartsTurnInfo::playerScores()
{
        QJsonArray jsonArr;
        auto scores = _scores->scores();
        for (const auto& score : scores.playerScores()) {
                QJsonObject jsonObj;
                jsonObj["name"] = score.name();
                jsonObj["value"] = score.score();
                jsonArr << jsonObj;
        }
        return jsonArr;
}

QJsonObject DartsTurnInfo::turnIndex()
{
        QJsonObject jsonObj;
        jsonObj["canUndo"] = _indexes->canUndo();
        jsonObj["canRedo"] = _indexes->canRedo();
        jsonObj["turnIndex"] = _indexes->index().turnIndex();
        return jsonObj;
}

QJsonObject DartsTurnInfo::finish()
{
        QJsonObject jsonObj;
        auto remaining = _scores->score().playerScore();
        jsonObj["targetRow"] = _finishes->suggestTargetRow(remaining, _indexes->index().turnIndex());
        return jsonObj;
}
