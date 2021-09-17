#include "dartspointsjsonservice.h"

QByteArray DartsInputModelsToJson::ctoJson(const QVector<const IModel<QUuid> *> &models) const
{
    using namespace ModelsContext;
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

