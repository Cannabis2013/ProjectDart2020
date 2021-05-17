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
                              const IPlayerModelsService*,
                              const QByteArray>
{
public:
    const QByteArray service(const IDartsModelsService* dartsModelsService,
                             const IPlayerModelsService* playerModelsService) override
    {
        auto models = dartsModelsService->dartsTournamentModels();
        QJsonArray arr = assembleJsonArrayFromModels(models,playerModelsService);
        auto json = QJsonDocument(arr).toJson();
        return json;
    }

private:
    QJsonArray assembleJsonArrayFromModels(const QVector<const IDartsTournament*>& models,
                                           const IPlayerModelsService* playerModelsService)
    {
        QJsonArray arr;
        for (const auto& model : models) {
            arr << assembleJsonObjectFromModel(model,playerModelsService);
        }
        return arr;
    }
    QJsonObject assembleJsonObjectFromModel(const IDartsTournament* model,
                                          const IPlayerModelsService* playerModelsService)
    {
        auto assignedPlayerIds = model->assignedPlayerIdentities();
        auto assignedPlayerNames = playerModelsService->assemblePlayerNamesFromIds(assignedPlayerIds);
        auto winnerId = model->winnerId();
        auto winnerName = playerModelsService->playerNameById(winnerId);
        QJsonObject jsonObject;
        jsonObject["title"] = model->title();
        jsonObject["gameMode"] = model->gameMode();
        jsonObject["keyPoint"] = model->keyPoint();
        jsonObject["displayHint"] = model->displayHint();
        jsonObject["inputHInt"] = model->inputHint();
        jsonObject["terminalKeyCode"] = model->terminalKeyCode();
        jsonObject["assignedPlayerIds"] = assembleJsonPlayerArray(model->assignedPlayerIdentities());
        jsonObject["assignedPlayerNames"] = assembleJsonByAssignedPlayerNames(assignedPlayerNames);
        jsonObject["winnerId"] = winnerId.toString(QUuid::WithoutBraces);
        jsonObject["winnerName"] = playerModelsService->playerNameById(model->winnerId());
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
    QJsonArray assembleJsonByAssignedPlayerNames(const QVector<QString>& names)
    {
        QJsonArray arr;
        for (const auto& name : names)
            arr << name;
        return arr;
    }
};



#endif // ASSEMBLEJSONDARTSTOURNAMENTMODELS_H
