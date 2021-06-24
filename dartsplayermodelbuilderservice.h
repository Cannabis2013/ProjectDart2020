#ifndef PLAYERMODELBUILDERSERVICE_H
#define PLAYERMODELBUILDERSERVICE_H

#include "dartscontrollerplayer.h"
#include "idartsplayermodelbuilderservice.h"
#include <QJsonDocument>
#include <qjsonobject.h>
#include <qjsonarray.h>
namespace DartsPointControllerContext {
    class DartsPlayerModelBuilderService : public
            IDartsPlayerModelBuilderService<IDartsControllerPlayer<QUuid,QString,QByteArray>,QString,QUuid,QByteArray>
    {
    public:
        typedef IDartsControllerPlayer<QUuid,QString,QByteArray> ControllerPlayer;
        QVector<const ModelsInterface *> createPlayerModelsByJson(const JsonFormat &json) const override
        {
            auto document = QJsonDocument::fromJson(json);
            auto playerDatas = document.array();
            QVector<const ControllerPlayer*> list;
            for (const auto &playerDataJsonValue : playerDatas) {
                auto obj = playerDataJsonValue.toObject();
                auto dartsPlayerModel = DartsControllerPlayer::createInstance();
                auto playerStringId = obj["playerId"].toString();
                dartsPlayerModel->setPlayerId(QUuid::fromString(playerStringId));
                dartsPlayerModel->setPlayerName(obj["playerName"].toString());
                list << dartsPlayerModel;
            }
            return list;
        }
        const ModelsInterface *createPlayerModelByValues(const IdFormat &id, const StringFormat &name) const override
        {
            auto playerModel = DartsControllerPlayer::createInstance();
            playerModel->setPlayerId(id);
            playerModel->setPlayerName(name);
            return playerModel;
        }
    };
}

#endif // PLAYERMODELBUILDERSERVICE_H
