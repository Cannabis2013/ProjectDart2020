#include "dartsinputjsonbuilder.h"

QByteArray DartsInputJsonBuilder::json(IModel<QUuid> *model, const DartsMetaModel &meta) const
{
    if(model != nullptr)
        return toByteArray(toJsonObject(model));
    return toByteArray(toDefaultJsonObject(meta));
}

QByteArray DartsInputJsonBuilder::json(const QVector<IModel<QUuid> *> &models) const
{
    return toByteArray(toJsonArray(models));
}

QJsonArray DartsInputJsonBuilder::toJsonArray(const QVector<IModel<QUuid> *> &models) const
{
    QJsonArray arr;
    for (const auto& model : models)
        arr << toJsonObject(model);
    return arr;
}

QJsonObject DartsInputJsonBuilder::toJsonObject(IModel<QUuid> *model) const
{
    using namespace ModelsContext;
    auto inputModel = dynamic_cast<const AbstractDartsInput*>(model);
    QJsonObject obj;
    obj["id"] = inputModel->id().toString(QUuid::WithoutBraces);
    obj["tournamentId"] = inputModel->tournamentId().toString(QUuid::WithoutBraces);
    obj["point"] = inputModel->point();
    obj["score"] = inputModel->score();
    obj["remainingScore"] = inputModel->remainingScore();
    obj["roundIndex"] = inputModel->roundIndex();
    obj["setIndex"] = inputModel->setIndex();
    obj["attemptIndex"] = inputModel->attempt();
    obj["inputPlayerId"] = inputModel->playerId().toString(QUuid::WithoutBraces);
    obj["inputPlayerName"] = inputModel->playerName();
    obj["hint"] = inputModel->hint();
    obj["modKeyCode"] = inputModel->modKeyCode();
    obj["middleValue"] = inputModel->middleValue();
    obj["currentMaximum"] = inputModel->currentMaximum();
    obj["currentMinimum"] = inputModel->currentMinimum();
    return obj;
}

QJsonObject DartsInputJsonBuilder::toDefaultJsonObject(const DartsMetaModel &meta) const
{
    QJsonObject obj;
    obj["tournamentId"] = toString(meta.tournamentId);
    obj["inputPlayerId"] = toString(meta.playerId);
    obj["inputPlayerName"] = meta.playerName;
    return obj;
}

QByteArray DartsInputJsonBuilder::toByteArray(const QJsonArray &arr) const
{
    return QJsonDocument(arr).toJson();
}
QByteArray DartsInputJsonBuilder::toByteArray(const QJsonObject &obj) const
{
    return QJsonDocument(obj).toJson();
}

QString DartsInputJsonBuilder::toString(const QUuid &id) const
{
    return id.toString(QUuid::WithoutBraces);
}
