#include "dartsinputjsonextractor.h"



IModel<QUuid> *DartsInputJsonExtractor::extractDartsPointFromJson(const QJsonValue &jsonValue)
{
    auto JsonObject = jsonValue.toObject();
    auto stringID = JsonObject["Id"].toString();
    auto id = QUuid::fromString(stringID);
    auto tournament = JsonObject["Tournament"].toString();
    auto tournamentId = QUuid::fromString(tournament);
    auto playerStringID = JsonObject["PlayerId"].toString();
    auto playerId = QUuid::fromString(playerStringID);
    auto roundIndex = JsonObject["RoundIndex"].toInt();
    auto setIndex = JsonObject["SetIndex"].toInt();
    auto attempt = JsonObject["Attempt"].toInt();
    auto pointValue = JsonObject["PointValue"].toInt();
    auto scoreValue = JsonObject["ScoreValue"].toInt();
    auto keyCode = JsonObject["KeyCode"].toInt();
    auto scoreHint = JsonObject["Hint"].toInt();
    auto scoreModel = DartsPointInput::createInstance()
            ->setId(id)
            ->setTournament(tournamentId)
            ->setPlayer(playerId)
            ->setRoundIndex(roundIndex)
            ->setSetIndex(setIndex)
            ->setAttempt(attempt)
            ->setPointValue(pointValue)
            ->setScoreValue(scoreValue)
            ->setModKeyCode(keyCode)
            ->setDisplayHint(scoreHint);
    return scoreModel;
}

IModel<QUuid> *DartsInputJsonExtractor::extractDartsScoreFromJson(const QJsonValue& jsonObject)
{
}
