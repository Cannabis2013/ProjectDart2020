#include "createdartspointsfromjson.h"

using namespace DartsDbContext;

QVector<const IModel<QUuid> *> CreateDartsPointsFromJson::create(const QByteArray &json) const
{
    auto arr = toJsonArray(json);
    return createInputsFromJsonArray(arr);
}

const QJsonArray CreateDartsPointsFromJson::toJsonArray(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto obj = document.object();
    return obj.value("DartsInputModels").toArray();
}

QVector<const IModel<QUuid>*> CreateDartsPointsFromJson::createInputsFromJsonArray(const QJsonArray &arr) const
{
    QVector<const IModel<QUuid>*> list;
    for (const auto& jsonValue : arr)
        list << toInputModel(jsonValue.toObject());
    return list;
}

const ModelsContext::IDartsInput *CreateDartsPointsFromJson::toInputModel(const QJsonObject &jsonObject) const
{
    auto pointModel = new ModelsContext::DartsInput;
    pointModel->setId(toId(jsonObject,"id"));
    pointModel->setTournament(toId(jsonObject,"tournament"));
    pointModel->setPlayerId(toId(jsonObject,"playerId"));
    pointModel->setRoundIndex(jsonObject["roundIndex"].toInt());
    pointModel->setSetIndex(jsonObject["setIndex"].toInt());
    pointModel->setAttempt(jsonObject["attemptIndex"].toInt());
    pointModel->setPoint(jsonObject["point"].toInt());
    pointModel->setScore(jsonObject.value("score").toInt());
    pointModel->setModKeyCode(jsonObject["keyCode"].toInt());
    pointModel->setHint(jsonObject["hint"].toInt());
    return pointModel;
}

QUuid CreateDartsPointsFromJson::toId(const QJsonObject &obj, const QString &key) const
{
    auto id = obj[key].toString();
    return QUuid::fromString(id);
}
