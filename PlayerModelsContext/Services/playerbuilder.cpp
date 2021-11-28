#include "PlayerModelsContext/Services/playerbuilder.h"
IModel<QUuid> *PlayerBuilder::createPlayer(const QByteArray &json) const
{
    auto obj = toJsonObject(json);
    return toModel(obj);
}

QVector<IModel<QUuid>*> PlayerBuilder::createPlayers(const QByteArray &json) const
{
    auto arr = toJsonArray(json);
    QVector<IModel<QUuid>*> playerModels;
    for (auto i = arr.begin();i != arr.end();i++) {
        auto JSONValue = *i;
        auto obj = JSONValue.toObject();
        playerModels.append(toModel(obj));
    }
    return playerModels;
}

QVector<PlayerBuilder::BaseModel *> PlayerBuilder::create(const Data &json) const
{
    auto obj = QJsonDocument::fromJson(json).object();
    QVector<BaseModel*> players;
    auto arr = obj.value("players").toArray();
    for (const auto &obj : arr)
        players << toModel(obj.toObject());
    return players;
}

PlayerModel *PlayerBuilder::toModel(const QJsonObject &obj) const
{
    auto playerId = toId(obj.value("playerId").toString());
    auto playerName = obj.value("playerName").toString();
    auto mail = obj.value("playerMail").toString();
    auto model = new PlayerModel;
    model->setId(playerId);
    model->setName(playerName);
    model->setEmail(mail);
    return model;
}

QJsonObject PlayerBuilder::toJsonObject(const QByteArray &json) const
{
    return QJsonDocument::fromJson(json).object();
}

QJsonArray PlayerBuilder::toJsonArray(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto arr = document.array();
    return arr;
}

QUuid PlayerBuilder::toId(const QString &stringId) const
{
    auto id = QUuid::fromString(stringId);
    if(id == QUuid())
        return QUuid::createUuid();
    return id;
}
