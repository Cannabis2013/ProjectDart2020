#include "addtotalscoretodartsinputsasjson.h"

void AddTotalScoreToDartsInputsAsJson::addTotalScoreToInputs(QByteArray &json, const int &initialPoint) const
{
    auto arr = toArray(json);
    auto playerIds = createPlayerIds(arr);
    addTotalScoresToJsonArray(arr,playerIds,initialPoint);
    json = toByteArray(arr);
}

QJsonArray AddTotalScoreToDartsInputsAsJson::toArray(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    if(document.isArray())
        return document.array();
    else
        return QJsonArray();
}

QVector<QUuid> AddTotalScoreToDartsInputsAsJson::createPlayerIds(const QJsonArray &arr) const
{
    QVector<QUuid> playerIds;
    for (const auto &jsonVal : arr) {
        auto jsonObject = jsonVal.toObject();
        auto playerId = QUuid(jsonObject.value("playerId").toString());
        if(!playerIds.contains(playerId))
            playerIds << playerId;
    }
    return playerIds;
}

void AddTotalScoreToDartsInputsAsJson::addTotalScoresToJsonArray(QJsonArray &arr, const QVector<QUuid> &playerIds,
                                                               const int &initialPoint) const
{
    for (const auto &playerId : playerIds)
        addTotalScoreToPlayerJson(arr,playerId,initialPoint);
}

void AddTotalScoreToDartsInputsAsJson::addTotalScoreToPlayerJson(QJsonArray &arr, const QUuid &playerId, const int &initialPoint) const
{
    auto tempTotalScore = initialPoint;
    for (int i = 0; i < arr.count(); ++i) {
        auto jsonValue = arr.at(i);
        auto jsonObject = jsonValue.toObject();
        auto pId = QUuid(jsonObject.value("playerId").toString());
        if(pId == playerId)
        {
            auto point = jsonObject.value("point").toInt();
            auto modKeyCode = jsonObject.value("modKeyCode").toInt();
            auto score = calculateScore(point,modKeyCode);
            tempTotalScore -= score;
            jsonObject["totalScore"] = tempTotalScore;
            arr.replace(i,jsonObject);
        }
    }
}

QByteArray AddTotalScoreToDartsInputsAsJson::toByteArray(const QJsonArray &arr) const
{
    auto document = QJsonDocument(arr);
    auto json = document.toJson();
    return json;
}

int AddTotalScoreToDartsInputsAsJson::calculateScore(const int &point, const int &modKeyCode) const
{
    auto p = point;
    if(modKeyCode == SingleModifer)
        return p;
    else if(modKeyCode == DoubleModifier)
        return p*2;
    else if(modKeyCode == TrippleModifier)
        return p*3;
    else if(modKeyCode == BullModifier)
        return 25;
    else if(modKeyCode == BullsEyeModifier)
        return 50;
    throw  "Illegal modkey value";
}
