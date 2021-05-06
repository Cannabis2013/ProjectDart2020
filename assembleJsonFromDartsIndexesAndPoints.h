#ifndef ASSEMBLEJSONFROMDARTSINDEXESANDPOINTS_H
#define ASSEMBLEJSONFROMDARTSINDEXESANDPOINTS_H

#include "iternaryservice.h"
#include <qjsondocument.h>
#include <qjsonarray.h>
#include <qjsonobject.h>
#include "idartsmodelsservice.h"
#include "iplayermodelsservice.h"
#include "iplayermodel.h"

class AssembleJsonFromDartsIndexesAndPoints : public
        ITernaryService<const QUuid&,
                        const IDartsModelsService*,
                        const IPlayerModelsService<IPlayerModel<QUuid,QString>>*,
                        const QByteArray>
{
public:
    const QByteArray service(const QUuid& tournament,
                             const IDartsModelsService* _dartsModelsService,
                             const IPlayerModelsService<IPlayerModel<QUuid,QString>>* _playerModelsService) override
    {
        auto indexes = _dartsModelsService->dartsIndexes(tournament);
        auto playerIds = _dartsModelsService->tournamentAssignedPlayers(tournament);
        auto playerNames = _playerModelsService->assemblePlayerNamesFromIds(playerIds);
        QJsonObject obj;
        obj["indexes"] = _assembleJsonDartsIndexes->service(indexes);
        obj["playerEntities"] = _JsonArrayPlayerNamesAndIds->service(playerIds,playerNames);
        obj["scoreEntities"] = _JsonArrayDartsPoints->service(tournament,_dartsModelsService);
    }
};

#endif // ASSEMBLEJSONFROMDARTSINDEXESANDPOINTS_H
