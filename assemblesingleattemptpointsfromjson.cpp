#include "assemblesingleattemptpointsfromjson.h"

QVector<const IDartsPointInput*> AssembleSingleAttemptPointsFromJson::service(const QJsonArray &arr)
{
    QVector<const IDartsPointInput*> list;
    for (const auto& jsonValue : arr) {
        auto jsonObject = jsonValue.toObject();
        auto model = assembleModelFromJsonObject(jsonObject);
        list << model;
    }
    return list;
}
const DartsPointInput *AssembleSingleAttemptPointsFromJson::assembleModelFromJsonObject(const QJsonObject &jsonObject)
{
    auto stringID = jsonObject["id"].toString();
    auto id = QUuid::fromString(stringID);
    auto tournament = jsonObject["tournament"].toString();
    auto tournamentId = QUuid::fromString(tournament);
    auto playerStringID = jsonObject["playerId"].toString();
    auto playerId = QUuid::fromString(playerStringID);
    auto roundIndex = jsonObject["roundIndex"].toInt();
    auto setIndex = jsonObject["setIndex"].toInt();
    auto attempt = jsonObject["attempt"].toInt();
    auto point = jsonObject["point"].toInt();
    auto score = jsonObject.value("score").toInt();
    auto keyCode = jsonObject["keyCode"].toInt();
    auto scoreHint = jsonObject["hint"].toInt();
    auto pointModel = DartsPointInput::createInstance()
            ->setId(id)
            ->setTournament(tournamentId)
            ->setPlayer(playerId)
            ->setRoundIndex(roundIndex)
            ->setSetIndex(setIndex)
            ->setAttempt(attempt)
            ->setPoint(point)
            ->setScore(score)
            ->setModKeyCode(keyCode)
            ->setDisplayHint(scoreHint);
    return pointModel;
}
