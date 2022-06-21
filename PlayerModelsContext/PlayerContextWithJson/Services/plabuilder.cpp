#include "plabuilder.h"
#include "playermodel.h"
#include <QByteArray>
#include <QJsonArray>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qvector.h>
#include <PlayerModelsContext/Contracts/DbSLAs/iplayer.h>

PlaBuilder::BaseModel *PlaBuilder::createPlayer(const QByteArray &json) const
{
        auto obj = toJsonObject(json);
        return toModel(obj);
}

QVector<IPlayer*> PlaBuilder::createPlayers(const QByteArray &json) const
{
        auto arr = toJsonArray(json);
        QVector<IPlayer*> playerModels;
        for (auto i = arr.begin();i != arr.end();i++) {
                auto JSONValue = *i;
                auto obj = JSONValue.toObject();
                playerModels.append(toModel(obj));
        }
        return playerModels;
}

QVector<PlaBuilder::BaseModel *> PlaBuilder::convert(const DataFormat &json) const
{
        auto obj = QJsonDocument::fromJson(json).object();
        QVector<BaseModel*> players;
        auto arr = obj.value("Players").toArray();
        for (const auto &obj : arr)
                players << toModel(obj.toObject());
        return players;
}

PlayerModel *PlaBuilder::toModel(const QJsonObject &obj) const
{
        auto playerId = toId(obj.value("playerId").toString());
        auto playerName = obj.value("name").toString();
        auto mail = obj.value("mail").toString();
        auto model = new PlayerModel;
        model->setId(playerId);
        model->setName(playerName);
        model->setEmail(mail);
        return model;
}

QJsonObject PlaBuilder::toJsonObject(const QByteArray &json) const
{
        return QJsonDocument::fromJson(json).object();
}

QJsonArray PlaBuilder::toJsonArray(const QByteArray &json) const
{
        auto document = QJsonDocument::fromJson(json);
        auto arr = document.array();
        return arr;
}

QUuid PlaBuilder::toId(const QString &stringId) const
{
        auto id = QUuid::fromString(stringId);
        if(id == QUuid())
                return QUuid::createUuid();
        return id;
}
