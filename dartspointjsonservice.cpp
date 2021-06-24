#include "dartspointjsonservice.h"

using namespace DartsPointControllerContext;

DartsPointJsonService::IdFormat DartsPointJsonService::getWinnerIdByJson(const JsonFormat &json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto jsonObject = document.object();
    auto winnerStringId = jsonObject.value("playerId").toString();
    auto winnerId = QUuid(winnerStringId);
    return winnerId;
}

DartsPointJsonService::JsonFormat DartsPointJsonService::createJsonByDartsPoint(const PointModel *model) const
{
    QJsonObject obj;
    obj["playerId"] = model->playerId().toString(QUuid::WithoutBraces);
    obj["point"] = model->point();
    obj["score"] = model->score();
    obj["totalScore"] = model->totalScore();
    obj["modKeyCode"] = model->modKeyCode();
    auto json = QJsonDocument(obj).toJson();
    return json;
}

DartsPointJsonService::JsonFormat DartsPointJsonService::createJsonByWinnerName(const QString &winnerName) const
{
    QJsonObject jsonObject = {{"winner",winnerName}};
    auto json = QJsonDocument(jsonObject).toJson();
    return json;
}

DartsPointJsonService::JsonFormat DartsPointJsonService::createJsonByTournamentId(const IdFormat &tournamentId) const
{
    QJsonObject jsonObject = {{"tournamentId",tournamentId.toString(QUuid::WithoutBraces)}};
    auto json = QJsonDocument(jsonObject).toJson();
    return json;
}

