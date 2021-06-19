#include "getordereddartspointsbyjson.h"

using namespace DartsPointControllerContext;

QVector<const IGetOrderedDartsPointByJson::ControllerPoint *> GetOrderedDartsPointsByJson::getOrderedDartsPointsFromJson(const QByteArray &json) const
{
    QVector<const ControllerPoint*> orderedPointModels;
    auto document = QJsonDocument::fromJson(json);
    auto arr = document.array();
    for (const auto& jsonVal : arr) {
        auto jsonObject = jsonVal.toObject();
        auto dartsPoint = DartsControllerPoint::fromJsonObject(jsonObject);
        orderedPointModels << dartsPoint;
    }
    return orderedPointModels;
}
