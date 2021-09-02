#include "dartspointsjsonservice.h"

using namespace ModelsContext;


QByteArray DartsModelsCreateJsonFromPoints::createJson(const QVector<const IModel<QUuid> *> &models) const
{
    QJsonArray pointsJsonArray;
    for (const auto& model : models) {
        auto dartsPoint = dynamic_cast<const IDartsInput*>(model);
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

