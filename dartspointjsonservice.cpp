#include "dartspointjsonservice.h"

using namespace DartsPointSingleAttemptContext;

QVector<const SingleAttemptJsonService::ExtendedInputValues *> DartsPointJsonService::assembleExtendedInputModelsFromJson(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto scoreData = document.array();
    QVector<const ExtendedInputValues*> extendedValueModels;
    for (const auto &jsonVal : scoreData) {
        auto obj = jsonVal.toObject();
        ExtendedInputValues* extendedValueModel = new ExtendedInputValues;
        extendedValueModel->pointValue = obj.value("point").toInt();
        extendedValueModel->modKeyCode = obj.value("modKeyCode").toInt();
        auto playerStringId = obj.value("playerId").toString();
        extendedValueModel->playerId = QUuid::fromString(playerStringId);
        extendedValueModels << extendedValueModel;
    }
    return extendedValueModels;
}

QVector<const SingleAttemptJsonService::PlayerDetailsStruct *> DartsPointJsonService::assemblePlayerDetailsStructsFromJson(const QByteArray& json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto playerDatas = document.array();
    QVector<const PlayerDetailsStruct*> list;
    for (const auto &playerDataJsonValue : playerDatas) {
        auto obj = playerDataJsonValue.toObject();
        PlayerDetailsStruct* playerDetails = new PlayerDetailsStruct;
        auto playerStringId = obj["playerId"].toString();
        playerDetails->playerId = QUuid::fromString(playerStringId);
        playerDetails->playerName = obj["playerName"].toString();
        list << playerDetails;
    }
    return list;
}

const SingleAttemptJsonService::PlayerDetailsStruct *DartsPointJsonService::assembleWinnerStructFromJson(const QByteArray& json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto jsonObject = document.object();
    auto winnerStringId = jsonObject.value("playerId").toString();
    auto winnerId = QUuid::fromString(winnerStringId);
    PlayerDetailsStruct* winnerStruct = new PlayerDetailsStruct;
    winnerStruct->playerId = winnerId;
    return winnerStruct;
}

QByteArray DartsPointJsonService::assembleJsonAddPointValues(const QUuid &tournamentId, const int &roundIndex,
                                                                          const int &setIndex, const int &attemptIndex,
                                                                          const QUuid &winnerId, const QUuid &playerId,
                                                                          const int &point, const int& score,const int &modKeyCode) const
{
    QJsonObject obj;
    obj["tournamentId"] = tournamentId.toString(QUuid::WithoutBraces);
    obj["roundIndex"] = roundIndex;
    obj["setIndex"] = setIndex;
    obj["attempt"] = attemptIndex;
    obj["winnerId"] = winnerId.toString(QUuid::WithoutBraces);
    obj["playerId"] = playerId.toString(QUuid::WithoutBraces);
    obj["point"] = point;
    obj["score"] = score;
    obj["modKeyCode"] = modKeyCode;
    auto json = QJsonDocument(obj).toJson();
    return json;
}

QByteArray DartsPointJsonService::assembleJsonWinnerName(const QString &winnerName) const
{
    QJsonObject jsonObject = {{"winner",winnerName}};
    auto json = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);
    return json;
}
