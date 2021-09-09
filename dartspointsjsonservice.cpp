#include "dartspointsjsonservice.h"

using namespace ModelsContext;


QByteArray DartsModelsCreateJsonFromPoints::toJson(const QVector<const IModel<QUuid> *> &models) const
{
    QJsonArray pointsJsonArray;
    for (const auto& model : models) {
        auto inputModel = dynamic_cast<const IDartsInput*>(model);
        QJsonObject playerJsonObject;
        auto playerId = inputModel->playerId();
        playerJsonObject["playerId"] = playerId.toString(QUuid::WithoutBraces);
        playerJsonObject["point"] = inputModel->point();
        playerJsonObject["modKeyCode"] = inputModel->modKeyCode();
        playerJsonObject["score"] = inputModel->score();
        pointsJsonArray << playerJsonObject;
    }
    auto json = QJsonDocument(pointsJsonArray).toJson();
    return json;
}

