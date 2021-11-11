#ifndef DCPLAYERBUILDER_H
#define DCPLAYERBUILDER_H

#include "DartsController/DCPlayerSLAs/idcplayerbuilder.h"
#include "DartsController/DCPlayerServices/dcplayer.h"

#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>

class DCPlayerBuilder : public IDCPlayerBuilder
{
public:
    DCPlayer createPlayer(const DCInput &input) const override
    {
        DCPlayer player;
        player.id = input.playerId;
        player.name = input.playerName;
        return player;
    }
    virtual QVector<DCPlayer> createPlayers(const QJsonArray &arr) const override
    {
        return toModels(arr);
    }
    virtual DCPlayer createWinner(const QJsonObject &obj) const override
    {
        return toModel(obj);
    }
private:
    QJsonArray toJsonArray(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        if(!document.isArray())
            throw "JSON NOT ARRAY";
        return document.array();
    }
    QJsonObject toJsonObject(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        if(!document.isObject())
            throw "JSON NOT OBJECT";
        return document.object();
    }
    QVector<DCPlayer> toModels(const QJsonArray &arr) const
    {
        QVector<DCPlayer> players;
        for (const auto &value : arr)
            players << toModel(value.toObject());
        return players;
    }
    DCPlayer toModel(const QJsonObject &obj) const
    {
        DCPlayer player;
        player.id = toId(obj.value("playerId").toString());
        player.name = obj.value("playerName").toString();
        return player;
    }
    DCPlayer toWinnerModel(const QJsonObject &obj) const
    {
        DCPlayer player;
        player.id = toId(obj.value("winnerId").toString(""));
        player.name = obj.value("winnerName").toString("");
        return player;
    }
    QUuid toId(const QString &string) const
    {
        return QUuid::fromString(string);
    }
};
#endif // DARTSPLAYERBUILDERSERVICE_H
