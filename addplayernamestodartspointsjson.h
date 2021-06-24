#ifndef ADDPLAYERNAMESTODARTSPOINTSJSON_H
#define ADDPLAYERNAMESTODARTSPOINTSJSON_H

#include "iaddplayernamestojsonentity.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

namespace DartsPointControllerContext {
    class AddPlayerNamestoDartsPointsJson : public IAddPlayerNamesToJsonEntity<QByteArray>
    {
    public:
        void addPlayerNamesToJson(JSonFormat &json, const PlayerService* playerService) const override
        {
            auto document = QJsonDocument::fromJson(json);
            auto arr = document.array();
            QJsonArray newArr = createJsonArrayWithPlayerNames(arr,playerService);
            auto newDocument = QJsonDocument(newArr);
            json = newDocument.toJson();
        }
    private:
        QJsonArray createJsonArrayWithPlayerNames(const QJsonArray &arr, const PlayerService* playerService) const
        {
            QJsonArray newArr;
            for (const auto &j : arr) {
                auto obj = j.toObject();
                auto playerId = QUuid(obj.value("playerId").toString());
                auto playerName = playerService->playerName(playerId);
                obj["playerName"] = playerName;
                newArr << obj;
            }
            return newArr;
        }
    };
}

#endif // ADDPLAYERNAMESTODARTSPOINTSJSON_H
