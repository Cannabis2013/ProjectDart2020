#ifndef ADDPLAYERNAMESTODARTSINPUTSASJSON_H
#define ADDPLAYERNAMESTODARTSINPUTSASJSON_H

#include "DartsController/DCJsonSLAs/iaddplayernamestojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class AddPlayerNamestoDartsInputsAsJson : public IAddPlayerNamesToJson
{
public:
    void addPlayerNamesToJson(QByteArray &json, IDCScoreModels* scoresService) const override
    {
        auto document = QJsonDocument::fromJson(json);
        auto arr = document.array();
        QJsonArray newArr = createJsonArrayWithPlayerNames(arr,scoresService);
        auto newDocument = QJsonDocument(newArr);
        json = newDocument.toJson();
    }
private:
    QJsonArray createJsonArrayWithPlayerNames(const QJsonArray &arr, IDCScoreModels* scoresService) const
    {
        QJsonArray newArr;
        for (const auto &j : arr) {
            auto obj = j.toObject();
            auto playerId = QUuid(obj.value("playerId").toString());
            obj["playerName"] = getPlayerName(playerId,scoresService->scores());
            newArr << obj;
        }
        return newArr;
    }
    QString getPlayerName(const QUuid &id, const QVector<DCScoreModel> &scoreModels) const
    {
        for (const auto &scoreModel : scoreModels) {
            if(scoreModel.playerId == id)
                return scoreModel.playerName;
        }
        return QString();
    }
};
#endif // ADDPLAYERNAMESTODARTSINPUTSASJSON_H
