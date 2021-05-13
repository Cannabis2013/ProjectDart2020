#include "dartsmultiattemptjsonservice.h"

const IDartsMultiAttemptJsonService::KeyInputValues *DartsMultiAttemptJsonService::assemblePointStructFromJson(const QByteArray &json) const
{
    KeyInputValues* inputValueModel = new KeyInputValues;
    auto jsonObject = QJsonDocument::fromJson(json).object();
    inputValueModel->score = jsonObject.value("score").toInt();
    return inputValueModel;
}

const IDartsMultiAttemptJsonService::ExtendedInputValues *DartsMultiAttemptJsonService::assembleExtendedInputModelFromJson(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto obj = document.object();
    ExtendedInputValues* extendedValueModel = new ExtendedInputValues;
    auto playerStringId = obj.value("playerId").toString();
    extendedValueModel->playerId = QUuid::fromString(playerStringId);
    extendedValueModel->score = obj.value("score").toInt();
    return extendedValueModel;
}

QVector<const IDartsMultiAttemptJsonService::ExtendedInputValues *> DartsMultiAttemptJsonService::assembleExtendedInputModelsFromJson(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto scoreData = document.array();
    QVector<const ExtendedInputValues*> extendedValueModels;
    for (const auto &jsonVal : scoreData) {
        auto obj = jsonVal.toObject();
        ExtendedInputValues* extendedValueModel = new ExtendedInputValues;
        extendedValueModel->score = obj.value("score").toInt();
        auto playerStringId = obj.value("playerId").toString();
        extendedValueModel->playerId = QUuid::fromString(playerStringId);
        extendedValueModels << extendedValueModel;
    }
    return extendedValueModels;
}

QVector<const IDartsMultiAttemptJsonService::PlayerDetailsStruct *> DartsMultiAttemptJsonService::assemblePlayerDetailsStructsFromJson(const QByteArray &json) const
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

const IDartsMultiAttemptJsonService::PlayerDetailsStruct *DartsMultiAttemptJsonService::assembleWinnerStructFromJson(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto jsonObject = document.object();
    auto winnerStringId = jsonObject.value("playerId").toString();
    auto winnerId = QUuid::fromString(winnerStringId);
    PlayerDetailsStruct* winnerStruct = new PlayerDetailsStruct;
    winnerStruct->playerId = winnerId;
    return winnerStruct;
}

QByteArray DartsMultiAttemptJsonService::assembleJsonFromParameters(const QString &playerName, const int &score) const
{
    QJsonObject obj = {
        {"playerName",playerName},
        {"score",score}
    };
    auto json = QJsonDocument(obj).toJson(QJsonDocument::Compact);
    return json;
}

const IDartsMultiAttemptJsonService::DartsIndexes *DartsMultiAttemptJsonService::assembleDartsIndexesFromJson(const QByteArray &json) const
{
    DartsIndexes* indexes = new DartsIndexes;
    auto jsonObject = QJsonDocument::fromJson(json).object();
    indexes->totalTurns = jsonObject.value("totalTurns").toInt();
    indexes->turns = jsonObject.value("turnIndex").toInt();
    indexes->roundIndex = jsonObject.value("roundIndex").toInt();
    indexes->setIndex = jsonObject.value("setIndex").toInt();
    return indexes;
}

QByteArray DartsMultiAttemptJsonService::assembleJsonDartsScore(const QString &playerName, const int &score) const
{
    QJsonObject jsonObject;
    jsonObject["playerName"] = playerName;
    jsonObject["score"] = score;
    auto document = QJsonDocument(jsonObject);
    auto json = document.toJson();
    return json;
}

QByteArray DartsMultiAttemptJsonService::assembleJsonTurnValues(const bool &canUndo,
                                                                const bool &canRedo,
                                                                const int &roundIndex,
                                                                const QString &currentPlayerName,
                                                                const QString &targetRow) const
{
    QJsonObject jsonObject = {
        {"canUndo", canUndo},
        {"canRedo",canRedo},
        {"roundIndex",roundIndex},
        {"currentUserName",currentPlayerName},
        {"targetRow",targetRow}
    };
    auto json = QJsonDocument(jsonObject).toJson();
    return json;
}

QByteArray DartsMultiAttemptJsonService::assembleJsonAddScoreValues(const QUuid &tournamentId, const int &roundIndex,
                                                                    const int &setIndex,const QUuid &winnerId,
                                                                    const QUuid &playerId,const int& score) const
{
    QJsonObject obj;
    obj["tournamentId"] = tournamentId.toString(QUuid::WithoutBraces);
    obj["roundIndex"] = roundIndex;
    obj["setIndex"] = setIndex;
    obj["winnerId"] = winnerId.toString(QUuid::WithoutBraces);
    obj["playerId"] = playerId.toString(QUuid::WithoutBraces);
    obj["score"] = score;
    auto json = QJsonDocument(obj).toJson();
    return json;
}

QByteArray DartsMultiAttemptJsonService::assembleJsonWinnerName(const QString &winnerName) const
{
    QJsonObject jsonObject = {{"winner",winnerName}};
    auto json = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);
    return json;
}


QByteArray DartsMultiAttemptJsonService::assembleJsonDartsMultiAttemptScores(const IPlayerScoreService *scoreService) const
{
    auto count = scoreService->playersCount();
    QJsonArray playerScoreEntities;
    for (int i = 0; i < count; ++i) {
        QJsonObject obj;
        auto playerName = scoreService->playerNameByIndex(i);
        auto score = scoreService->playerScore(i);
        obj["playerName"] = playerName;
        obj["score"] = score;
        playerScoreEntities.append(obj);
    };
    auto document = QJsonDocument(playerScoreEntities);
    auto json = document.toJson(QJsonDocument::Compact);
    return json;
}
