#ifndef LOCALPLAYERSCONTEXT_H
#define LOCALPLAYERSCONTEXT_H

#include "PlayerModelsContext/playermodelscontext.h"
#include "PlayerModelsContext/DbServices/localplayersdbcontext.h"
#include "PlayerModelsContext/Services/createplayerfromjson.h"
#include "PlayerModelsContext/Services/createplayermodels.h"
#include "PlayerModelsContext/Services/getplayersfromdb.h"
#include "createjsonfromplayers.h"

#include <removemodelsfromdb.h>
class LocalPlayersContext : public PlayerModelsContext
{
public:
    LocalPlayersContext()
    {
        using namespace PlayersContext;
        setModelsDbContext(new LocalPlayersDbContext);
        setCreatePlayerModel(new CreatePlayerFromJson);
        setCreatePlayerModels(new CreatePlayerModels);
        setGetPlayerModelsFromDb(new GetPlayersFromDb);
        setDartsPlayerJsonBuilder(new CreateJsonFromPlayers);
        setRemoveFromDb(new RemoveModelsFromDb);
    }
};
#endif // LOCALPLAYERSCONTEXT_H
