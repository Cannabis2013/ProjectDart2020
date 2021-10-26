#include "dartsinputbuilder.h"

IModel<QUuid> *DartsInputBuilder::createInput(const QUuid &tournamentId, const QUuid &playerId, const int &remainingScore) const
{
    auto inputModel = new ModelsContext::DartsInput;
    inputModel->setTournamentId(tournamentId);
    inputModel->setPlayerId(playerId);
    inputModel->setRemainingScore(remainingScore);
    return inputModel;
}

IModel<QUuid> *DartsInputBuilder::createInput(const QByteArray &json) const
{
    auto jsonObject = toJsonObject(json);
    return toInputModel(jsonObject);
}
QVector<IModel<QUuid> *> DartsInputBuilder::createInputs(const QByteArray &json) const
{
    auto arr = toJsonArray(json);
    return createInputsFromJsonArray(arr);
}

const QJsonArray DartsInputBuilder::toJsonArray(const QByteArray &json) const
{
    return QJsonDocument::fromJson(json).array();
}

QVector<IModel<QUuid>*> DartsInputBuilder::createInputsFromJsonArray(const QJsonArray &arr) const
{
    QVector<IModel<QUuid>*> list;
    for (const auto& jsonValue : arr)
        list << toInputModel(jsonValue.toObject());
    return list;
}

ModelsContext::IDartsInput *DartsInputBuilder::toInputModel(const QJsonObject &obj) const
{
    auto inputModel = new ModelsContext::DartsInput;
    inputModel->setId(obj.value("id").toString(QUuid::createUuid().toString(QUuid::WithoutBraces)));
    inputModel->setTournamentId(toId(obj,"tournamentId"));
    inputModel->setPlayerId(toId(obj,"inputPlayerId"));
    inputModel->setPlayerName(obj.value("inputPlayerName").toString());
    inputModel->setRoundIndex(obj["roundIndex"].toInt());
    inputModel->setSetIndex(obj["setIndex"].toInt());
    inputModel->setAttempt(obj["attemptIndex"].toInt());
    inputModel->setPoint(obj.value("point").toInt());
    inputModel->setScore(obj.value("score").toInt());
    inputModel->setModKeyCode(obj["modKeyCode"].toInt());
    inputModel->setHint(obj.value("hint").toInt(DisplayHint));
    inputModel->setMiddleValue(obj.value("middleValue").toDouble());
    inputModel->setCurrentMaximum(obj.value("currentMaximum").toInt());
    inputModel->setCurrentMinimum(obj.value("currentMinimum").toInt());
    inputModel->setRemainingScore(obj.value("remainingScore").toInt());
    return inputModel;
}

QUuid DartsInputBuilder::toId(const QJsonObject &obj, const QString &key) const
{
    auto id = obj.value(key).toString();
    return QUuid::fromString(id);
}

const QJsonObject DartsInputBuilder::toJsonObject(const QByteArray &json) const
{
    return QJsonDocument::fromJson(json).object();
}
