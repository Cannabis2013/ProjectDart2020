#include "dartspointsjsonservice.h"

using namespace DartsModelsContext;


QByteArray DartsModelsCreateJsonFromPoints::createJson(const QVector<const IPlayerInput *> &models) const
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

