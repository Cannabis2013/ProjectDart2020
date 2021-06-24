#ifndef DARTSPLAYERBUILDERSERVICE_H
#define DARTSPLAYERBUILDERSERVICE_H

#include "idartsplayerbuilderservice.h"
#include "dartsplayer.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace DartsScoreControllerContext {
    class DartsPlayerBuilderService : public
            IDartsPlayerBuilderService<IDartsPlayer<QUuid,QString>,QUuid,QString,QByteArray>
    {
    public:
        const PlayerInterface *buildPlayerModelByJson(const JsonFormat &json) const override
        {
            auto document = QJsonDocument::fromJson(json);
            auto obj = document.object();
            auto playerModel = DartsPlayer::createInstance();
            auto playerStringId = obj["playerId"].toString();
            playerModel->setPlayerId(QUuid::fromString(playerStringId));
            playerModel->setPlayerName(obj["playerName"].toString());
            return playerModel;
        }
        QVector<const PlayerInterface *> buildPlayerModelsByJson(const JsonFormat &json) override
        {
            auto document = QJsonDocument::fromJson(json);
            auto playerDatas = document.array();
            QVector<const PlayerInterface*> playerModels;
            for (const auto &playerDataJsonValue : playerDatas) {
                auto obj = playerDataJsonValue.toObject();
                auto playerModel = DartsPlayer::createInstance();
                auto playerStringId = obj.value("playerId").toString();
                playerModel ->setPlayerId(QUuid::fromString(playerStringId));
                playerModel ->setPlayerName(obj.value("playerName").toString());
                playerModels << playerModel ;
            }
            return playerModels;
        }
        const PlayerInterface *createPlayerModelByValues(const IdFormat &id, const StringFormat &name) const override
        {
            auto playerModel = DartsPlayer::createInstance();
            playerModel->setPlayerId(id);
            playerModel->setPlayerName(name);
            return playerModel;
        }
    };
}

#endif // DARTSPLAYERBUILDERSERVICE_H
