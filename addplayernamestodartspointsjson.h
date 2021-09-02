#ifndef ADDPLAYERNAMESTODARTSPOINTSJSON_H
#define ADDPLAYERNAMESTODARTSPOINTSJSON_H

#include "iaddplayernamestojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class AddPlayerNamestoDartsPointsJson : public IAddPlayerNamesToJson
{
public:
    void addPlayerNamesToJson(QByteArray &json, IDCScoresService* scoresService) const override
    {
        auto document = QJsonDocument::fromJson(json);
        auto arr = document.array();
        QJsonArray newArr = createJsonArrayWithPlayerNames(arr,scoresService);
        auto newDocument = QJsonDocument(newArr);
        json = newDocument.toJson();
    }
private:
    QJsonArray createJsonArrayWithPlayerNames(const QJsonArray &arr, IDCScoresService* scoresService) const
    {
        QJsonArray newArr;
        for (const auto &j : arr) {
            auto obj = j.toObject();
            auto playerId = QUuid(obj.value("playerId").toString());
            obj["playerName"] = getPlayerName(playerId,scoresService->tuples());
            newArr << obj;
        }
        return newArr;
    }
    QString getPlayerName(const QUuid &id, const QVector<DCContext::DCPTuple> &tuples) const
    {
        for (const auto &tuple : tuples) {
            if(tuple.id == id)
                return tuple.name;
        }
        return QString();
    }
};
#endif // ADDPLAYERNAMESTODARTSPOINTSJSON_H
