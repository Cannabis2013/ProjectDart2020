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
    pointModel->setId(jsonObject.value("id").toString(QUuid::createUuid().toString(QUuid::WithoutBraces)));
    pointModel->setTournament(toId(jsonObject,"tournamentId"));
    pointModel->setPlayerId(toId(jsonObject,"inputPlayerId"));
    pointModel->setPlayerName(jsonObject.value("inputPlayerName").toString());
    pointModel->setRoundIndex(jsonObject["roundIndex"].toInt());
    pointModel->setSetIndex(jsonObject["setIndex"].toInt());
    pointModel->setAttempt(jsonObject["attemptIndex"].toInt());
    pointModel->setPoint(jsonObject["point"].toInt());
    pointModel->setScore(jsonObject.value("score").toInt());
    pointModel->setModKeyCode(jsonObject["modKeyCode"].toInt());
    pointModel->setHint(jsonObject["hint"].toInt(DisplayHint));
    return pointModel;
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
