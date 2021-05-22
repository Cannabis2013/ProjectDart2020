#include "dartspointsingleattemptjsonservice.h"

QVector<const IDartsSingleAttemptPointJsonService::ExtendedInputValues *> DartsPointSingleAttemptJsonService::assembleExtendedInputModelsFromJson(const QByteArray &json) const
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

QVector<const IDartsSingleAttemptPointJsonService::PlayerDetailsStruct *> DartsPointSingleAttemptJsonService::assemblePlayerDetailsStructsFromJson(const QByteArray& json) const
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

const IDartsSingleAttemptPointJsonService::PlayerDetailsStruct *DartsPointSingleAttemptJsonService::assembleWinnerStructFromJson(const QByteArray& json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto jsonObject = document.object();
    auto winnerStringId = jsonObject.value("playerId").toString();
    auto winnerId = QUuid::fromString(winnerStringId);
    PlayerDetailsStruct* winnerStruct = new PlayerDetailsStruct;
    winnerStruct->playerId = winnerId;
    return winnerStruct;
}

QByteArray DartsPointSingleAttemptJsonService::assembleJsonFromParameters(const QString &playerName, const int &pointValue, const int &scoreValue, const int &modKeyCode) const
{
    QJsonObject obj = {
        {"playerName",playerName},
        {"point",pointValue},
        {"score",scoreValue},
        {"keyCode",modKeyCode}
    };
    auto json = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    return json;
}

const IDartsSingleAttemptPointJsonService::DartsIndexes *DartsPointSingleAttemptJsonService::assembleDartsIndexesFromJson(const QByteArray &json) const
{
    DartsIndexes* indexes = new DartsIndexes;
    auto jsonObject = QJsonDocument::fromJson(json).object();
    indexes->totalTurns = jsonObject.value("totalTurns").toInt();
    indexes->turns = jsonObject.value("turnIndex").toInt();
    indexes->roundIndex = jsonObject.value("roundIndex").toInt();
    indexes->setIndex = jsonObject.value("setIndex").toInt();
    indexes->attemptIndex = jsonObject.value("attemptIndex").toInt();
    return indexes;
}

QByteArray DartsPointSingleAttemptJsonService::assembleJsonAddPointValues(const QUuid &tournamentId, const int &roundIndex,
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

QByteArray DartsPointSingleAttemptJsonService::assembleJsonWinnerName(const QString &winnerName) const
{
    QJsonObject jsonObject = {{"winner",winnerName}};
    auto json = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);
    return json;
}

const IDartsSingleAttemptPointJsonService::ExtendedInputValues * DartsPointSingleAttemptJsonService::assembleExtendedInputModelFromJson(const QByteArray& json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto obj = document.object();
    ExtendedInputValues* extendedValueModel = new ExtendedInputValues;
    auto playerStringId = obj.value("playerId").toString();
    extendedValueModel->playerId = QUuid::fromString(playerStringId);
    extendedValueModel->pointValue = obj.value("point").toInt();
    extendedValueModel->modKeyCode = obj.value("modKeyCode").toInt();
    return extendedValueModel;
}

QByteArray DartsPointSingleAttemptJsonService::assembleJsonFromParameters(const QString &playerName, const int &pointValue, const int &scoreValue) const
{
    QJsonObject obj = {
        {"playerName",playerName},
        {"point",pointValue},
        {"score",scoreValue}
    };
    auto json = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    return json;
}
