#ifndef PLAYERMODELBUILDERSERVICE_H
#define PLAYERMODELBUILDERSERVICE_H

#include "dartscontrollerplayer.h"
#include "idartsplayermodelbuilderservice.h"
#include <QJsonDocument>
#include <qjsonobject.h>
#include <qjsonarray.h>
namespace DartsPointSingleAttemptContext {
    class DartsPlayerModelBuilderService : public
            IDartsPlayerModelBuilderService<IDartsControllerPlayer<QUuid,QString>,QByteArray>
    {
    public:
        typedef IDartsControllerPlayer<QUuid,QString> ControllerPlayer;
        QVector<const ModelsInterface *> buildPlayerModelsByJson(const JsonFormat &json) const override
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
    };
}

#endif // PLAYERMODELBUILDERSERVICE_H
