#include "createjsonfromplayermodels.h"

using namespace ModelsContext;

QByteArray CreateJsonFromPlayerModels::createJson(QVector<const IModel<QUuid> *> models) const
{
    QJsonArray arr = createJsonArray(models);
    return createByteArray(arr);
}

QJsonArray CreateJsonFromPlayerModels::createJsonArray(QVector<const IModel<QUuid> *> models) const
{
    QJsonArray arr;
    for (auto model : models)
        arr << createJsonObject(model);
    return arr;
}

QJsonObject CreateJsonFromPlayerModels::createJsonObject(const IModel<QUuid> *model) const
{
    auto playerModel = dynamic_cast<const IPlayerModel*>(model);
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
