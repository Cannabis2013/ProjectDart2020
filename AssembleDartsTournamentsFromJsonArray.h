#ifndef ASSEMBLEDARTSTOURNAMENTFROMJSONARRAY_H
#define ASSEMBLEDARTSTOURNAMENTFROMJSONARRAY_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "dartstournament.h"

namespace DartsModelsContext {
    class AssembleDartsTournamentsFromJsonArray :
            public IUnaryService<const QJsonObject&,QVector<const IDartsTournament*>>
    {
    public:
        QVector<const IDartsTournament*> service(const QJsonObject& json) override
        {
            using namespace DartsModelsContext;
            QVector<const IDartsTournament*> list;
            auto jsonArray = json.value("DartsTournaments").toArray();
            for (const auto& jsonValue : jsonArray) {
                auto model = buildModelByJsonValue(jsonValue);
                list << model;
            }
            return list;
        }
    private:
        const IDartsTournament* buildModelByJsonValue(const QJsonValue& jsonValue)
        {
            auto jsonObject = jsonValue.toObject();
            auto dartsTournamentModel = DartsTournament::createInstance();
            dartsTournamentModel->setId(QUuid(jsonObject.value("id").toString()));
            dartsTournamentModel->setTitle(jsonObject.value("title").toString());
            dartsTournamentModel->setGameMode(jsonObject.value("gameMode").toInt());
            dartsTournamentModel->setKeyPoint(jsonObject.value("keyPoint").toInt());
            dartsTournamentModel->setAttempts(jsonObject.value("attempts").toInt());
            dartsTournamentModel->setTerminalKeyCode(jsonObject.value("terminalKeyCode").toInt());
            dartsTournamentModel->setDisplayHint(jsonObject.value("displayHint").toInt());
            dartsTournamentModel->setInputMode(jsonObject.value("inputHint").toInt());
            dartsTournamentModel->setStatus(jsonObject.value("status").toInt());
            dartsTournamentModel->setWinnerId(QUuid(jsonObject.value("winnerId").toString("")));
            auto arr = jsonObject.value("assignedPlayerIds").toArray();
            auto assignedPlayerIds = buildPlayerIdsByJsonArray(arr);
            dartsTournamentModel->setAssignedPlayerIdentities(assignedPlayerIds);
            return dartsTournamentModel;
        }
        QVector<QUuid> buildPlayerIdsByJsonArray(const QJsonArray& arr)
        {
            QVector<QUuid> assignedPlayerIds;
            for (const auto& jsonValue : arr) {
                auto stringId = jsonValue.toString();
                auto id = QUuid::fromString(stringId);
                assignedPlayerIds << id;
            }
            return assignedPlayerIds;
        }
    };
}

#endif // ASSEMBLEDARTSTOURNAMENTFROMJSONARRAY_H
