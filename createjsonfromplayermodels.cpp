#include "createjsonfromplayermodels.h"

using namespace DartsModelsContext;

QByteArray CreateJsonFromPlayerModels::createJson(QVector<const IPlayerModel *> models) const
{
    QJsonArray arr = createJsonArray(models);
    return createByteArray(arr);
}

QJsonArray CreateJsonFromPlayerModels::createJsonArray(QVector<const IPlayerModel *> models) const
{
    QJsonArray arr;
    for (auto model : models)
        arr << createJsonObject(model);
    return arr;
}

QJsonObject CreateJsonFromPlayerModels::createJsonObject(const IPlayerModel *model) const
{
    auto playerModel = dynamic_cast<const PlayerModel*>(model);
    QJsonObject obj;
    obj["Id"] = playerModel->id().toString();
    obj["UserName"] = playerModel->playerName();
    obj["Mail"] = playerModel->email();
    return obj;
}

QByteArray CreateJsonFromPlayerModels::createByteArray(const QJsonArray &arr) const
{
    return QJsonDocument(arr).toJson();
}
