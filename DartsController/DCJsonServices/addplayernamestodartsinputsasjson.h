#ifndef ADDPLAYERNAMESTODARTSINPUTSASJSON_H
#define ADDPLAYERNAMESTODARTSINPUTSASJSON_H

#include "DartsController/DCJsonSLAs/iaddplayernamestojson.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>

class AddPlayerNamestoDartsInputsAsJson : public IAddPlayerNamesToJson
{
public:
    void addPlayerNamesToJson(QByteArray &json, IDCScoresService* scoresService, const IDCInputJsonKeys *keys) const override
    {
        auto document = QJsonDocument::fromJson(json);
        auto arr = document.array();
        QJsonArray newArr = createJsonArrayWithPlayerNames(arr,scoresService,keys);
        auto newDocument = QJsonDocument(newArr);
        json = newDocument.toJson();
    }
private:
    QJsonArray createJsonArrayWithPlayerNames(const QJsonArray &arr, IDCScoresService* scoresService,
                                              const IDCInputJsonKeys *keys) const
    {
        QJsonArray newArr;
        for (const auto &j : arr) {
            auto obj = j.toObject();
            auto playerId = QUuid(obj.value(keys->playerId()).toString());
            obj[keys->playerName()] = getPlayerName(playerId,scoresService->scoreModels());
            newArr << obj;
        }
        return newArr;
    }
    QString getPlayerName(const QUuid &id, const QVector<DCContext::DCScoreModel> &scoreModels) const
    {
        for (const auto &scoreModel : scoreModels) {
            if(scoreModel.playerId == id)
                return scoreModel.playerName;
        }
        return QString();
    }
};
#endif // ADDPLAYERNAMESTODARTSINPUTSASJSON_H
