#include "dartsinputjsonextractor.h"

QVector<const IModel<QUuid>*> DartsInputJsonExtractor::service(const QJsonArray &arr)
{
    QVector<const IModel<QUuid>*> list;
    for (const auto& jsonValue : arr) {
        auto jsonObject = jsonValue.toObject();
        auto model = assembleModelFromJsonObject(jsonObject);
        list << model;
    }
    return list;
}
const DartsPointInput *DartsInputJsonExtractor::assembleModelFromJsonObject(const QJsonObject &jsonObject)
{
    auto stringID = jsonObject["Id"].toString();
    auto id = QUuid::fromString(stringID);
    auto tournament = jsonObject["Tournament"].toString();
    auto tournamentId = QUuid::fromString(tournament);
    auto playerStringID = jsonObject["PlayerId"].toString();
    auto playerId = QUuid::fromString(playerStringID);
    auto roundIndex = jsonObject["RoundIndex"].toInt();
    auto setIndex = jsonObject["SetIndex"].toInt();
    auto attempt = jsonObject["Attempt"].toInt();
    auto pointValue = jsonObject["PointValue"].toInt();
    auto keyCode = jsonObject["KeyCode"].toInt();
    auto scoreHint = jsonObject["Hint"].toInt();
    auto pointModel = DartsPointInput::createInstance()
            ->setId(id)
            ->setTournament(tournamentId)
            ->setPlayer(playerId)
            ->setRoundIndex(roundIndex)
            ->setSetIndex(setIndex)
            ->setAttempt(attempt)
            ->setPointValue(pointValue)
            ->setModKeyCode(keyCode)
            ->setDisplayHint(scoreHint);
    return pointModel;
}
