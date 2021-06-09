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

QByteArray DartsPointJsonService::buildJsonByIndexesAndPoint(const DartsIndexes *indexes,
                                                             const PointModel *model) const
{
    QJsonObject obj;
    obj["tournamentId"] = model->tournamentId().toString(QUuid::WithoutBraces);
    obj["roundIndex"] = indexes->roundIndex();
    obj["setIndex"] = indexes->setIndex();
    obj["attempt"] = indexes->attemptIndex();
    obj["playerId"] = model->playerId().toString(QUuid::WithoutBraces);
    obj["point"] = model->point();
    obj["score"] = model->accumulatedScore();
    obj["modKeyCode"] = model->modKeyCode();
    auto json = QJsonDocument(obj).toJson();
    return json;
}
