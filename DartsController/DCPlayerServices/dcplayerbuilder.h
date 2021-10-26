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
    DCPlayer createModel(const QUuid &id, const QString &name) const override
    {
        DCPlayer player;
        player.id = id;
        player.name = name;
        return player;
    }
    virtual QVector<DCPlayer> createPlayers(const QByteArray &json) const override
    {
        auto arr = toJsonArray(json);
        return toModels(arr);
    }
private:
    QJsonArray toJsonArray(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        if(!document.isArray())
            throw "JSON NOT ARRAY";
        return document.array();
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
    QUuid toId(const QString &string) const
    {
        return QUuid::fromString(string);
    }
};
#endif // DARTSPLAYERBUILDERSERVICE_H
