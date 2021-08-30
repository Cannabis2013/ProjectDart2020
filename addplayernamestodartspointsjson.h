#ifndef ADDPLAYERNAMESTODARTSPOINTSJSON_H
#define ADDPLAYERNAMESTODARTSPOINTSJSON_H

#include "iaddplayernamestojsonentity.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class AddPlayerNamestoDartsPointsJson : public IAddPlayerNamesToJsonEntity
{
public:
    void addPlayerNamesToJson(QByteArray &json, const IDCScoresService* scoresService) const override
    {
        auto document = QJsonDocument::fromJson(json);
        auto arr = document.array();
        QJsonArray newArr = createJsonArrayWithPlayerNames(arr,playerService);
        auto newDocument = QJsonDocument(newArr);
        json = newDocument.toJson();
    }
private:
    QJsonArray createJsonArrayWithPlayerNames(const QJsonArray &arr, const IDCScoresService* scoresService) const
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
#endif // ADDPLAYERNAMESTODARTSPOINTSJSON_H
