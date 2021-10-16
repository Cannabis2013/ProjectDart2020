#include "dartsinputjsonbuilder.h"

QByteArray DartsInputJsonBuilder::dartsInputJson(IModel<QUuid> *model) const
{
    return toByteArray(toJsonObject(model));
}

QByteArray DartsInputJsonBuilder::dartsInputsJson(const QVector<IModel<QUuid> *> &models) const
{
    return toByteArray(createJsonArray(models));
}

QJsonArray DartsInputJsonBuilder::createJsonArray(const QVector<IModel<QUuid> *> &models) const
{
    QJsonArray arr;
    for (const auto& model : models)
        arr << toJsonObject(model);
    return arr;
}

QJsonObject DartsInputJsonBuilder::toJsonObject(IModel<QUuid> *model) const
{
    using namespace ModelsContext;
    auto dartsPointModel = dynamic_cast<const IDartsInput*>(model);
    QJsonObject jsonObject;
    jsonObject["id"] = dartsPointModel->id().toString(QUuid::WithoutBraces);
    jsonObject["tournamentId"] = dartsPointModel->tournamentId().toString(QUuid::WithoutBraces);
    jsonObject["point"] = dartsPointModel->point();
    jsonObject["score"] = dartsPointModel->score();
    jsonObject["roundIndex"] = dartsPointModel->roundIndex();
    jsonObject["setIndex"] = dartsPointModel->setIndex();
    jsonObject["attemptIndex"] = dartsPointModel->attempt();
    jsonObject["inputPlayerId"] = dartsPointModel->playerId().toString(QUuid::WithoutBraces);
    jsonObject["inputPlayerName"] = dartsPointModel->playerName();
    jsonObject["hint"] = dartsPointModel->hint();
    jsonObject["modKeyCode"] = dartsPointModel->modKeyCode();
    return jsonObject;
}
QByteArray DartsInputJsonBuilder::toByteArray(const QJsonArray &arr) const
{
    return QJsonDocument(arr).toJson();
}
QByteArray DartsInputJsonBuilder::toByteArray(const QJsonObject &obj) const
{
    return QJsonDocument(obj).toJson();
}
