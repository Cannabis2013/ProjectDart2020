#ifndef ASSEMBLEDARTSPLAYERSBYJSON_H
#define ASSEMBLEDARTSPLAYERSBYJSON_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "dartsplayer.h"

namespace DartsScoreMultiAttemptContext
{
    class AssembleDartsPlayersByJson : public
            IUnaryService<const QByteArray&,
                          QVector<const IDartsPlayer*>>
    {
    public:
        QVector<const IDartsPlayer*> service(const QByteArray& json) override
        {
            auto document = QJsonDocument::fromJson(json);
            auto playerDatas = document.array();
            QVector<const IDartsPlayer*> list;
            for (const auto &playerDataJsonValue : playerDatas) {
                auto obj = playerDataJsonValue.toObject();
                DartsPlayer* playerDetails = new DartsPlayer;
                auto playerStringId = obj.value("playerId").toString();
                playerDetails->setPlayerId(QUuid::fromString(playerStringId));
                playerDetails->setPlayerName(obj.value("playerName").toString());
                list << playerDetails;
            }
            return list;
        }
    };
}


#endif // ASSEMBLEDARTSPLAYERSBYJSON_H
