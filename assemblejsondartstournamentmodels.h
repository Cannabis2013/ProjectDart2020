#ifndef ASSEMBLEJSONDARTSTOURNAMENTMODELS_H
#define ASSEMBLEJSONDARTSTOURNAMENTMODELS_H

#include "ibinaryservice.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "idartstournament.h"
#include <qvector.h>
#include "idartsmodelsservice.h"
#include "iplayermodelsservice.h"
#include "iplayermodel.h"

class AssembleJsonDartsTournamentModels :
        public IBinaryService<const IDartsModelsService*,
                              const IPlayerModelsService<IPlayerModel<QUuid,QString>>*,
                              const QByteArray>
{
public:
    const QByteArray service(const IDartsModelsService* dartsModelsService,
                             const IPlayerModelsService<IPlayerModel<QUuid,QString>>* playerModelsService) override
    {
        auto models = dartsModelsService->getDartsTournamentModels();
        QJsonArray arr = assembleJSonArrayFromModels(models,playerModelsService);
        auto json = QJsonDocument(arr).toJson();
        return json;
    }

private:
    QJsonArray assembleJSonArrayFromModels(const QVector<const IDartsTournament<QUuid,QString>*>& models,
                                           const IPlayerModelsService<IPlayerModel<QUuid,QString>>* playerModelsService)
    {
        QJsonArray arr;
        for (const auto& model : models) {
            arr << assembleJsonObjectFromModel(model,playerModelsService);
        }
        return arr;
    }
    QJsonObject assembleJsonObjectFromModel(const IDartsTournament<QUuid,QString>* model,
                                          const IPlayerModelsService<IPlayerModel<QUuid,QString>>* playerModelsService)
    {
        QJsonObject jsonObject;
        jsonObject["title"] = model->title();
        jsonObject["gameMode"] = model->gameMode();
        jsonObject["keyPoint"] = model->keyPoint();
        jsonObject["displayHint"] = model->displayHint();
        jsonObject["inputHInt"] = model->inputHint();
        jsonObject["terminalKeyCode"] = model->terminalKeyCode();
        jsonObject["assignedPlayerIds"] = assembleJsonPlayerArray(model->assignedPlayerIdentities());
        jsonObject["winnerId"] = model->winnerId().toString(QUuid::WithoutBraces);
        jsonObject["winnerName"] = playerModelsService->playerNameFromId(model->winnerId());
        return jsonObject;
    }
    QJsonArray assembleJsonPlayerArray(const QVector<QUuid>& playerIds)
    {
        QJsonArray arr;
        for (const auto& playerId : playerIds) {
            auto playerStringId = playerId.toString(QUuid::WithoutBraces);
            arr << playerStringId;
        }
        return arr;
    }
};



#endif // ASSEMBLEJSONDARTSTOURNAMENTMODELS_H
