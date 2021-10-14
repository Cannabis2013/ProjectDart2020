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

PlayersContext::PlayerModel *CreatePlayersFromJson::toModel(const QJsonObject &obj) const
{
    auto stringID = obj.value("playerId").toString();
    auto playerId = QUuid::fromString(stringID);
    auto playerName = obj.value("playerName").toString();
    auto mail = obj.value("playerMail").toString();
    auto model = PlayersContext::PlayerModel::createInstance()
            ->setId(playerId)
            ->setUserName(playerName)
            ->setEmail(mail);
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
