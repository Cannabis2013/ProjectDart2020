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

QVector<const SingleAttemptJsonService::ControllerPlayer *> DartsPointJsonService::assemblePlayerDetailsStructsFromJson(const QByteArray& json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto playerDatas = document.array();
    QVector<const ControllerPlayer*> list;
    for (const auto &playerDataJsonValue : playerDatas) {
        auto obj = playerDataJsonValue.toObject();
        auto dartsPlayerModel = new DartsControllerPlayer();
        auto playerStringId = obj["playerId"].toString();
        dartsPlayerModel->setPlayerId(QUuid::fromString(playerStringId));
        dartsPlayerModel->setPlayerName(obj["playerName"].toString());
        list << dartsPlayerModel;
    }
    return list;
}

const SingleAttemptJsonService::ControllerPlayer *DartsPointJsonService::assembleWinnerStructFromJson(const QByteArray& json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto jsonObject = document.object();
    auto winnerStringId = jsonObject.value("playerId").toString();
    auto winnerId = QUuid::fromString(winnerStringId);
    auto dartsPlayerModel = new DartsControllerPlayer;
    dartsPlayerModel->setPlayerId(winnerId);
    return dartsPlayerModel;
}

QByteArray DartsPointJsonService::assembleJsonAddPointValues(const QUuid &tournamentId, const DartsIndexes *indexes,
                                                                          const QUuid &winnerId, const PointModel *model) const
{
    QJsonObject obj;
    obj["tournamentId"] = tournamentId.toString(QUuid::WithoutBraces);
    obj["roundIndex"] = indexes->roundIndex();
    obj["setIndex"] = indexes->setIndex();
    obj["attempt"] = indexes->attemptIndex();
    obj["winnerId"] = winnerId.toString(QUuid::WithoutBraces);
    obj["playerId"] = model->playerId().toString(QUuid::WithoutBraces);
    obj["point"] = model->point();
    obj["score"] = model->accumulatedScore();
    obj["modKeyCode"] = model->modKeyCode();
    auto json = QJsonDocument(obj).toJson();
    return json;
}

QByteArray DartsPointJsonService::assembleJsonWinnerName(const QString &winnerName) const
{
    QJsonObject jsonObject = {{"winner",winnerName}};
    auto json = QJsonDocument(jsonObject).toJson(QJsonDocument::Compact);
    return json;
}
