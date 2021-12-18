#include "dartsinputstojson.h"
QByteArray DartsInputsToJson::create(const QVector<FromData*> &models, QByteArray &byteArray) const
{
    auto json = fromByteArray(byteArray);
    json["InputModels"] = toJsonArray(models);
    return toByteArray(json);
}

QJsonObject DartsInputsToJson::fromByteArray(const QByteArray &byteArray) const
{
    return QJsonDocument::fromJson(byteArray).object();
}

QByteArray DartsInputsToJson::toByteArray(const QJsonObject &obj) const
{
    return QJsonDocument(obj).toJson();
}

QJsonArray DartsInputsToJson::toJsonArray(const QVector<IModel<QUuid> *> &models) const
{
    QJsonArray arr;
    for (const auto& model : models)
        arr << toJsonObject(model);
    return arr;
}

QJsonObject DartsInputsToJson::toJsonObject(IModel<QUuid> *model) const
{
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
    obj["maximumValue"] = inputModel->currentMaximum();
    obj["minimumValue"] = inputModel->currentMinimum();
    obj["inGame"] = inputModel->inGame();
    return obj;
}
