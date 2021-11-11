#ifndef LOCALPLAYERSCONTEXT_H
#define LOCALPLAYERSCONTEXT_H
#include "PlayerModelsContext/playermodelscontext.h"
#include "PlayerModelsContext/Services/getplayersfromdb.h"
#include "PlayerModelsContext/DbServices/playersdbcontext.h"
#include "FileOperationsContext/Services/readbytearray.h"
#include "FileOperationsContext/Services/writebytearray.h"
#include "PlayerModelsContext/Services/createjsonfromplayermodels.h"
#include "PlayerModelsContext/Services/createplayersfromjson.h"
class LocalPlayersContext
{
public:
    AbstractPlayersContext *createLocalContext()
    {
        auto context = new PlayerModelsContext;
        context->setDbContext(new PlayersDbContext(new ReadByteArray,new WriteByteArray));
        context->setGetPlayerModelsFromDb(new GetPlayersFromDb);
        context->setJsonBuilder(new CreateJsonFromPlayerModels);
        context->setPlayerBuilder(new CreatePlayersFromJson);
        context->dbContext()->fetchModels(context->playerBuilder());
        return context;
    }
};
#endif // LOCALPLAYERSCONTEXT_H
