#ifndef ASSEMBLEDARTSTOURNAMENTFROMJSONARRAY_H
#define ASSEMBLEDARTSTOURNAMENTFROMJSONARRAY_H

#include "iunaryservice.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "dartstournament.h"

class AssembleDartsTournamentsFromJsonArray :
        public IUnaryService<const QJsonObject&,QVector<const IDartsTournament*>>
{
public:
    QVector<const IDartsTournament*> service(const QJsonObject& json) override
    {
        QVector<const IDartsTournament*> list;
        auto jsonArray = json.value("DartsTournaments").toArray();
        for (const auto& jsonValue : jsonArray) {
            auto jsonObject = jsonValue.toObject();
            auto stringId = jsonObject.value("id").toString();
            auto id = QUuid::fromString(stringId);
            auto title = jsonObject.value("title").toString();
            auto gameMode = jsonObject.value("gameMode").toInt();
            auto keyPoint = jsonObject.value("keyPoint").toInt();
            auto terminalKeyCode = jsonObject.value("terminalKeyCode").toInt();
            auto displayHint = jsonObject.value("displayHint").toInt();
            auto inputHint = jsonObject.value("inputHint").toInt();
            auto attempts = jsonObject.value("attempts").toInt();
            auto winnerStringId = jsonObject.value("winnerId").toString();
            auto winnerId = QUuid::fromString(winnerStringId);
            auto assignedPlayerIdsJsonArray = jsonObject.value("assignedPlayerIds").toArray();
            auto assignedPlayerIds = assembleAssignedPlayerIdsFromJsonArray(assignedPlayerIdsJsonArray);
            auto model = buildModelFromParameters(id,title,gameMode,keyPoint,terminalKeyCode,
                                                  displayHint,inputHint,attempts,winnerId,
                                                  assignedPlayerIds);
            list << model;
        }
        return list;
    }
private:
    const IDartsTournament* buildModelFromParameters(const QUuid& id,
                                                     const QString &title,
                                                     const int &gameMode,
                                                     const int &keyPoint,
                                                     const int &terminalKeyCode,
                                                     const int &displayHint,
                                                     const int &inputHint,
                                                     const int &attempts,
                                                     const QUuid& winnerId,
                                                     const QVector<QUuid>& assignedPlayerIds)
    {
        auto model = DartsTournament::createInstance()
                ->setTitle(title)
                ->setKeyPoint(keyPoint)
                ->setGameMode(gameMode)
                ->setAttempts(attempts)
                ->setTerminalKeyCode(terminalKeyCode)
                ->setDisplayHint(displayHint)
                ->setInputMode(inputHint)
                ->setAssignedPlayerIdentities(assignedPlayerIds)
                ->setWinnerId(winnerId)
                ->setId(id);
        return model;
    }
    const QVector<QUuid> assembleAssignedPlayerIdsFromJsonArray(const QJsonArray& arr)
    {
        QVector<QUuid> list;
        for (const auto& jsonValue : arr) {
            auto assignedPlayerStringId = jsonValue.toString();
            auto assignedPlayerId = QUuid::fromString(assignedPlayerStringId);
            list << assignedPlayerId;
        }
        return list;
    }
};

#endif // ASSEMBLEDARTSTOURNAMENTFROMJSONARRAY_H
