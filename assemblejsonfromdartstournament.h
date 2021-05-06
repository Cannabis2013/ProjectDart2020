#ifndef ASSEMBLEJSONFROMDARTSTOURNAMENT_H
#define ASSEMBLEJSONFROMDARTSTOURNAMENT_H

#include "ibinaryservice.h"
#include "idartstournament.h"
#include <quuid.h>
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include "iplayermodelsservice.h"

class AssembleJsonFromDartsTournament :
        public IBinaryService<const IDartsTournament<QUuid,QString>*,
                              const IPlayerModelsService<IPlayerModel<QUuid,QString>>*,
                              const QByteArray>
{
public:


    // IBinaryService interface
public:
    const QByteArray service(const IDartsTournament<QUuid,QString>* dartsTournamentModel,
                             const IPlayerModelsService<IPlayerModel<QUuid,QString>>* playerService) override
    {
        QJsonObject obj;
        obj["title"] = dartsTournamentModel->title();
        obj["winnerName"] = playerService->playerNameFromId(dartsTournamentModel->winnerId());
        obj["gameMode"] = dartsTournamentModel->gameMode();
        obj["attempts"] = dartsTournamentModel->attempts();
        obj["keyPoint"] = dartsTournamentModel->keyPoint();
        obj["displayHint"] = dartsTournamentModel->displayHint();
        obj["inputHint"] = dartsTournamentModel->inputHint();
        auto playerIds = dartsTournamentModel->assignedPlayerIdentities();
        auto assignedPlayerNames = playerService->assemblePlayerNamesFromIds(playerIds);
        QJsonArray arr;
        for (const auto &assignedPlayerName : assignedPlayerNames)
            arr << assignedPlayerName;
        obj["assignedPlayerNames"] = arr;
        auto json = QJsonDocument(obj).toJson();
        return json;
    }
};



#endif // ASSEMBLEJSONFROMDARTSTOURNAMENT_H
