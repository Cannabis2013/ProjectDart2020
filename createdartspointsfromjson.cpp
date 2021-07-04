#include "createdartspointsfromjson.h"

using namespace DartsModelsContext;

QVector<const IPlayerInput*> CreateDartsPointsFromJson::create(const QByteArray &json) const
{
    auto arr = createArray(json);
    return createInputsFromJsonArray(arr);
}

const QJsonArray CreateDartsPointsFromJson::createArray(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto obj = document.object();
    return obj.value("players").toArray();
}

QVector<const IPlayerInput *> CreateDartsPointsFromJson::createInputsFromJsonArray(const QJsonArray &arr) const
{
    QVector<const IPlayerInput*> list;
    for (const auto& jsonValue : arr)
        list << createInputFromJsonValue(jsonValue);
    return list;
}

const IPlayerInput *CreateDartsPointsFromJson::createInputFromJsonValue(const QJsonValue &jsonValue) const
{
    auto jsonObject = jsonValue.toObject();
    return  createModelFromJsonObject(jsonObject);
}

const DartsModelsContext::DartsPointInput *CreateDartsPointsFromJson::createModelFromJsonObject(const QJsonObject &jsonObject) const
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
    auto pointModel = DartsModelsContext::DartsPointInput::createInstance()
            ->setId(id)
            ->setTournament(tournamentId)
            ->setPlayerId(playerId)
            ->setRoundIndex(roundIndex)
            ->setSetIndex(setIndex)
            ->setAttempt(attempt)
            ->setPoint(point)
            ->setScore(score)
            ->setModKeyCode(keyCode)
            ->setHint(scoreHint);
    return pointModel;
}
