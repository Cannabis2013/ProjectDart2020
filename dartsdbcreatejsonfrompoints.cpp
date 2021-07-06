#include "dartsdbcreatejsonfrompoints.h"

using namespace DartsDbContext;

QByteArray DartsDbCreatejsonFromPoints::createJson(const QVector<const IPlayerInput *> &models) const
{
    QJsonArray arr = createJsonArray(models);
    return createByteArray(arr);

}

QJsonArray DartsDbCreatejsonFromPoints::createJsonArray(const QVector<const IPlayerInput *> &models) const
{
    QJsonArray arr;
    for (const auto& model : models)
        arr << createJsonObject(model);
    return arr;
}

QJsonObject DartsDbCreatejsonFromPoints::createJsonObject(const IPlayerInput *model) const
{
    using namespace DartsModelsContext;
    auto dartsPointModel = dynamic_cast<const IDartsPointInput*>(model);
    QJsonObject jsonObject;
    jsonObject["id"] = dartsPointModel->id().toString();
    jsonObject["tournament"] = dartsPointModel->tournamentId().toString();
    jsonObject["point"] = dartsPointModel->point();
    jsonObject["score"] = dartsPointModel->score();
    jsonObject["roundIndex"] = dartsPointModel->roundIndex();
    jsonObject["setIndex"] = dartsPointModel->setIndex();
    jsonObject["attempt"] = dartsPointModel->attempt();
    jsonObject["playerId"] = dartsPointModel->playerId().toString();
    jsonObject["hint"] = dartsPointModel->hint();
    jsonObject["keyCode"] = dartsPointModel->modKeyCode();
    return jsonObject;
}

QByteArray DartsDbCreatejsonFromPoints::createByteArray(const QJsonArray &arr) const
{
    QJsonObject obj;
    obj[_key] = arr;
    auto document = QJsonDocument(obj);
    auto json = document.toJson();
    return json;
}