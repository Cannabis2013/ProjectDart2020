#include "dartspointsjsonservice.h"

using namespace DartsModelsContext;

DartsPointsJsonService *DartsPointsJsonService::createInstance()
{
    return new DartsPointsJsonService;
}

DartsPointsJsonService::JsonFormat DartsModelsContext::DartsPointsJsonService::createJson(const IndexesInterface *indexes) const
{
    QJsonObject jsonObject;
    jsonObject["totalTurns"] = indexes->totalTurns();
    jsonObject["turnIndex"]  = indexes->turnIndex();
    jsonObject["roundIndex"] = indexes->roundIndex();
    jsonObject["setIndex"] = indexes->setIndex();
    jsonObject["attemptIndex"] = indexes->attemptIndex();
    auto json = QJsonDocument(jsonObject).toJson();
    return json;
}

DartsPointsJsonService::JsonFormat DartsModelsContext::DartsPointsJsonService::createJson(const QVector<const ModelInterface *> &models) const
{
    QJsonArray pointsJsonArray;
    for (const auto& model : models) {
        auto dartsPoint = dynamic_cast<const IDartsPointInput*>(model);
        QJsonObject playerJsonObject;
        auto playerId = dartsPoint->playerId();
        playerJsonObject["playerId"] = playerId.toString(QUuid::WithoutBraces);
        playerJsonObject["point"] = dartsPoint->point();
        playerJsonObject["modKeyCode"] = dartsPoint->modKeyCode();
        pointsJsonArray << playerJsonObject;
    }
    auto json = QJsonDocument(pointsJsonArray).toJson();
    return json;
}
