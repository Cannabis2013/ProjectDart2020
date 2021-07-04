#include "createjsonfromdartspoints.h"

using namespace DartsModelsContext;

QByteArray CreateJsonFromDartsPoints::createJson(const QVector<const IPlayerInput *> &models) const
{
    QJsonArray arr = createJsonArray(models);
    return createByteArray(arr);

}

QJsonArray CreateJsonFromDartsPoints::createJsonArray(const QVector<const IPlayerInput *> &models) const
{
    QJsonArray arr;
    for (const auto& model : models)
        arr << createJsonObject(model);
    return arr;
}

QJsonObject CreateJsonFromDartsPoints::createJsonObject(const IPlayerInput *model) const
{
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

QByteArray CreateJsonFromDartsPoints::createByteArray(const QJsonArray &arr) const
{
    QJsonObject obj;
    obj[_key] = arr;
    auto document = QJsonDocument(obj);
    auto json = document.toJson();
    return json;
}
