#include "dartsinputbuilder.h"

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

ModelsContext::IDartsInput *DartsInputBuilder::toInputModel(const QJsonObject &jsonObject) const
{
    auto pointModel = new ModelsContext::DartsInput;
    pointModel->setId(toId(jsonObject,"id"));
    pointModel->setTournament(toId(jsonObject,"tournamentId"));
    pointModel->setPlayerId(toId(jsonObject,"playerId"));
    pointModel->setPlayerName(jsonObject.value("playerName").toString());
    pointModel->setRoundIndex(jsonObject["roundIndex"].toInt());
    pointModel->setSetIndex(jsonObject["setIndex"].toInt());
    pointModel->setAttempt(jsonObject["attemptIndex"].toInt());
    pointModel->setPoint(jsonObject["point"].toInt());
    pointModel->setScore(jsonObject.value("score").toInt());
    pointModel->setModKeyCode(jsonObject["keyCode"].toInt());
    pointModel->setHint(jsonObject["hint"].toInt(DisplayHint));
    return pointModel;
}

QUuid DartsInputBuilder::toId(const QJsonObject &obj, const QString &key) const
{
    auto id = obj[key].toString();
    return QUuid::fromString(id);
}

const QJsonObject DartsInputBuilder::toJsonObject(const QByteArray &json) const
{
    return QJsonDocument::fromJson(json).object();
}
