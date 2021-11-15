#ifndef CREATEPLAYERSCONTEXT_H
#define CREATEPLAYERSCONTEXT_H
#include "PlayerModelsContext/playerscontext.h"
#include "PlayerModelsContext/Services/getplayersfromdb.h"
#include "PlayerModelsContext/DbServices/playersdbcontext.h"
#include "FileOperationsContext/Services/readbytearray.h"
#include "FileOperationsContext/Services/writebytearray.h"
#include "PlayerModelsContext/Services/createjsonfromplayermodels.h"
#include "PlayerModelsContext/Services/createplayersfromjson.h"
class CreatePlayersContext
{
public:
    static AbstractPlayersContext *createLocalContext()
    {
        auto context = new PlayersContext;
        context->setDbContext(new PlayersDbContext(new ReadByteArray,new WriteByteArray));
        context->setGetPlayerModelsFromDb(new GetPlayersFromDb);
        context->setJsonBuilder(new CreateJsonFromPlayerModels);
        context->setPlayerBuilder(new CreatePlayersFromJson);
        context->dbContext()->fetch(context->playerBuilder());
        return context;
    }
};
#endif // LOCALPLAYERSCONTEXT_H
