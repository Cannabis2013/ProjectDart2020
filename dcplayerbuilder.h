#ifndef DCPLAYERBUILDER_H
#define DCPLAYERBUILDER_H

#include "idcplayermodelbuilder.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <dcplayer.h>

class DCPlayerBuilder : public IDCPlayerModelBuilder
{
public:
    const DCContext::IDCPlayer *createModel(const QByteArray &json) const override
    {
        return toPlayerModel(toJsonObject(json));
    }
    QVector<const DCContext::IDCPlayer *> createModels(const QByteArray &json) override
    {
        QVector<const DCContext::IDCPlayer*> playerModels;
        for (const auto &jsonValue : toJsonArray(json))
            playerModels << toPlayerModel(jsonValue);
        return playerModels;
    }
    const DCContext::IDCPlayer *createModel(const QUuid &id, const QString &name) const override
    {
        return new DCContext::DCPlayer(id,name);
    }
private:
    const DCContext::IDCPlayer *toPlayerModel(const QJsonValue &jsonValue) const
    {
        auto obj = jsonValue.toObject();
        auto playerStringId = obj.value("playerId").toString();
        auto playerId = QUuid::fromString(playerStringId);
        auto playerName = obj.value("playerName").toString();
        return new DCContext::DCPlayer(playerId,playerName);
    }
    const DCContext::IDCPlayer *toPlayerModel(const QJsonObject &obj) const
    {
        auto playerStringId = obj.value("playerId").toString();
        auto playerId = QUuid::fromString(playerStringId);
        auto playerName = obj.value("playerName").toString();
        return new DCContext::DCPlayer(playerId,playerName);
    }
    QJsonArray toJsonArray(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        return document.array();
    }
    QJsonObject toJsonObject(const QByteArray &json) const
    {
        auto document = QJsonDocument::fromJson(json);
        return document.object();
    }
};
#endif // DARTSPLAYERBUILDERSERVICE_H
