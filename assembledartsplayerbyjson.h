#ifndef ASSEMBLEDARTSPLAYERBYJSON_H
#define ASSEMBLEDARTSPLAYERBYJSON_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include "dartsplayer.h"

namespace DartsScoreMultiAttemptContext {
    class AssembleDartsPlayerByJson : public
            IUnaryService<const QByteArray&,const IDartsPlayer*>
    {
    public:
        const IDartsPlayer* service(const QByteArray& json) override
        {
            auto document = QJsonDocument::fromJson(json);
            auto obj = document.object();
            DartsPlayer* playerModel = new DartsPlayer;
            auto playerStringId = obj["playerId"].toString();
            playerModel->playerId() = QUuid::fromString(playerStringId);
            playerModel->playerName() = obj["playerName"].toString();
            return playerModel;
        }
    };
}

#endif // ASSEMBLEDARTSPLAYERBYJSON_H
