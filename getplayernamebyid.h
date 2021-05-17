#ifndef GETPLAYERNAMEBYID_H
#define GETPLAYERNAMEBYID_H

#include "ibinaryservice.h"
#include "iplayermodelsservice.h"

class GetPlayerNameById : public
        IBinaryService<const QUuid&, const IPlayerModelsService*,QString>
{
public:
    QString service(const QUuid& playerId, const IPlayerModelsService* modelsService) override
    {
        auto playerName = modelsService->playerNameById(playerId);
        return playerName;
    }
};

#endif // GETPLAYERNAMEBYID_H
