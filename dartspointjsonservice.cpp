#include "dartspointjsonservice.h"

using namespace DartsPointControllerContext;

QUuid DartsPointJsonService::getWinnerIdByJson(const QByteArray& json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto jsonObject = document.object();
    auto winnerStringId = jsonObject.value("playerId").toString();
    auto winnerId = QUuid(winnerStringId);
    return winnerId;
}

QByteArray DartsPointJsonService::assembleJsonWinnerName(const QString &winnerName) const
{
    QJsonObject jsonObject = {{"winner",winnerName}};
    auto json = QJsonDocument(jsonObject).toJson();
    return json;
}

QByteArray DartsPointJsonService::convertDartsModelToJson(const PointModel *model) const
{
    QJsonObject obj;
    obj["tournamentId"] = model->tournamentId().toString(QUuid::WithoutBraces);
    obj["playerId"] = model->playerId().toString(QUuid::WithoutBraces);
    obj["point"] = model->point();
    obj["score"] = model->score();
    obj["totalScore"] = model->totalScore();
    obj["modKeyCode"] = model->modKeyCode();
    auto json = QJsonDocument(obj).toJson();
    return json;
}

QByteArray DartsPointJsonService::convertDartsIndexesToJson(const DartsIndexes *indexes) const
{
    QJsonObject obj;
    obj["roundIndex"] = indexes->roundIndex();
    obj["setIndex"] = indexes->setIndex();
    obj["attempt"] = indexes->attemptIndex();
    auto json = QJsonDocument(obj).toJson();
    return json;
}
