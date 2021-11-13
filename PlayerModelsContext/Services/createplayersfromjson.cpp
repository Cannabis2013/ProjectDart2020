#include "PlayerModelsContext/Services/createplayersfromjson.h"
QVector<IModel<QUuid> *> CreatePlayersFromJson::createPlayers(const QByteArray &json) const
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

IModel<QUuid> *CreatePlayersFromJson::createPlayer(const QByteArray &json) const
{
    auto obj = toJsonObject(json);
    return toModel(obj);
}

PlayerModel *CreatePlayersFromJson::toModel(const QJsonObject &obj) const
{
    auto playerId = toId(obj.value("playerId").toString());
    auto playerName = obj.value("playerName").toString();
    auto mail = obj.value("playerMail").toString();
    auto model = new PlayerModel;
    model->setId(playerId);
    model->setUserName(playerName);
    model->setEmail(mail);
    return model;
}

QJsonObject CreatePlayersFromJson::toJsonObject(const QByteArray &json) const
{
    return QJsonDocument::fromJson(json).object();
}

QJsonArray CreatePlayersFromJson::toJsonArray(const QByteArray &json) const
{
    auto document = QJsonDocument::fromJson(json);
    auto arr = document.array();
    return arr;
}

QUuid CreatePlayersFromJson::toId(const QString &stringId) const
{
    auto id = QUuid::fromString(stringId);
    if(id == QUuid())
        return QUuid::createUuid();
    return id;
}
