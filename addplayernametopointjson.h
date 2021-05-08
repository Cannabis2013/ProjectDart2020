#ifndef ADDPLAYERNAMETOPOINTJSON_H
#define ADDPLAYERNAMETOPOINTJSON_H

#include "iplayermodelsservice.h"
#include "ibinaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>

class AddPlayerNameToJsonPointModel :
        public IBinaryService<const QByteArray&,
                              const IPlayerModelsService*,
                              QByteArray>
{


    // IBinaryService interface
public:
    QByteArray service(const QByteArray& json,const IPlayerModelsService* playerService) override
    {
        auto document = QJsonDocument::fromJson(json);
        auto jsonObject = document.object();
        auto playerStringId = jsonObject.value("playerId").toString();
        auto playerId = QUuid::fromString(playerStringId);
        auto playerName = playerService->playerNameFromId(playerId);
        jsonObject["playerName"] = playerName;
        auto newDocument = QJsonDocument(jsonObject);
        auto newJSon = newDocument.toJson();
        return newJSon;
    }
};

#endif // ADDPLAYERNAMETOPOINTJSON_H
