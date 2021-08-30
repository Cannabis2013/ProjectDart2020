#ifndef DARTSPLAYERBUILDERSERVICE_H
#define DARTSPLAYERBUILDERSERVICE_H

#include "idscmodelbuilder.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <dcplayer.h>

namespace DSCContext {
    class DartsPlayerBuilderService : public IDSCModelBuilder<DCContext::IDCPlayer,QUuid,QString,QByteArray>
    {
    public:
        const Model *createModel(const Json &json) const override
        {
            return toPlayerModel(toJsonObject(json));
        }
        QVector<const Model *> createModels(const Json &json) override
        {
            QVector<const Model*> playerModels;
            for (const auto &jsonValue : toJsonArray(json))
                playerModels << toPlayerModel(jsonValue);
            return playerModels;
        }
        const Model *createModel(const Id &id, const String &name) const override
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
}
#endif // DARTSPLAYERBUILDERSERVICE_H
