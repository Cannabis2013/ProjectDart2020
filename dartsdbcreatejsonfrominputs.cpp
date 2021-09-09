#include "dartsdbcreatejsonfrominputs.h"

using namespace DartsDbContext;

QByteArray DartsDbCreatejsonFromInputs::toJson(const QVector<const IModel<QUuid> *> &models) const
{
    QJsonArray arr = createJsonArray(models);
    return createByteArray(arr);

}

QJsonArray DartsDbCreatejsonFromInputs::createJsonArray(const QVector<const IModel<QUuid> *> &models) const
{
    QJsonArray arr;
    for (const auto& model : models)
        arr << createJsonObject(model);
    return arr;
}

QJsonObject DartsDbCreatejsonFromInputs::createJsonObject(const IModel<QUuid> *model) const
{
    using namespace ModelsContext;
    auto dartsPointModel = dynamic_cast<const IDartsInput*>(model);
    QJsonObject jsonObject;
    jsonObject["id"] = dartsPointModel->id().toString(QUuid::WithoutBraces);
    jsonObject["tournament"] = dartsPointModel->tournamentId().toString(QUuid::WithoutBraces);
    jsonObject["point"] = dartsPointModel->point();
    jsonObject["score"] = dartsPointModel->score();
    jsonObject["roundIndex"] = dartsPointModel->roundIndex();
    jsonObject["setIndex"] = dartsPointModel->setIndex();
    jsonObject["attemptIndex"] = dartsPointModel->attempt();
    jsonObject["playerId"] = dartsPointModel->playerId().toString(QUuid::WithoutBraces);
    jsonObject["hint"] = dartsPointModel->hint();
    jsonObject["keyCode"] = dartsPointModel->modKeyCode();
    return jsonObject;
}

QByteArray DartsDbCreatejsonFromInputs::createByteArray(const QJsonArray &arr) const
{
    QJsonObject obj;
    obj[_key] = arr;
    auto document = QJsonDocument(obj);
    auto json = document.toJson();
    return json;
}
