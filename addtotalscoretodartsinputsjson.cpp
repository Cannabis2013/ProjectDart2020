#include "addtotalscoretodartsinputsjson.h"

using namespace DartsPointControllerContext;

void AddTotalScoreToDartsInputsJson::addTotalScoreToInputs(JsonFormat &json,const int &initialPoint) const
{
    auto arr = createArray(json);
    auto playerIds = buildListOfPlayerIds(arr);
    for (const auto &playerId : playerIds)
        addTotalScoresToJsonArray(arr,playerId,initialPoint);
    json = createJsonByArray(arr);
}

QJsonArray AddTotalScoreToDartsInputsJson::createArray(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    if(document.isArray())
        return document.array();
    else
        return QJsonArray();
}

QVector<QUuid> DartsPointControllerContext::AddTotalScoreToDartsInputsJson::buildListOfPlayerIds(const QJsonArray &arr) const
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

void AddTotalScoreToDartsInputsJson::addTotalScoresToJsonArray(QJsonArray &arr, const QUuid &playerId, const int &initialPoint) const
{
    auto tempTotalScore = initialPoint;
    for (int i = 0; i < arr.count(); ++i) {
        auto jsonValue = arr.at(i);
        auto jsonObject = jsonValue.toObject();
        auto pId = QUuid(jsonObject.value("playerId").toString());
        if(pId == playerId)
        {
            auto score = jsonObject["score"].toInt();
            tempTotalScore -= score;
            jsonObject["totalScore"] = tempTotalScore;
            arr.replace(i,jsonObject);
        }
    }
}

AddTotalScoreToDartsInputsJson::JsonFormat AddTotalScoreToDartsInputsJson::createJsonByArray(const QJsonArray &arr) const
{
    auto document = QJsonDocument(arr);
    auto json = document.toJson();
    return json;
}
