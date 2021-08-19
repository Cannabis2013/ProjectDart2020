#ifndef LOCALPLAYERSCONTEXT_H
#define LOCALPLAYERSCONTEXT_H

#include "playermodelscontext.h"
#include "localplayersdbcontext.h"
#include "createplayerfromjson.h"
#include "createplayermodels.h"
#include "getplayersfromdb.h"
#include "createjsonfromplayers.h"
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
    }
};

#endif // LOCALPLAYERSCONTEXT_H