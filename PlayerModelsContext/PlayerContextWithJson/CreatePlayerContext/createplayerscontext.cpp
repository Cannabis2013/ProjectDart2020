#include "createplayerscontext.h"
#include "playerscontext.h"
#include <Shared/filejsonio.h>
#include <PlayerModelsContext/PlayerContextWithJson/DbServices/loadplayermodels.h>
#include <PlayerModelsContext/PlayerContextWithJson/DbServices/playersdbcontext.h>
#include <PlayerModelsContext/PlayerContextWithJson/DbServices/saveplayermodels.h>
#include <PlayerModelsContext/PlayerContextWithJson/Services/getplayersfromdb.h>
#include <PlayerModelsContext/PlayerContextWithJson/Services/plabuilder.h>
#include <PlayerModelsContext/PlayerContextWithJson/DataServices/plajsonbuilder.h>
#include <PlayerModelsContext/PlayerContextWithJson/ModelsServices/duplicatechecker.h>

AbstractPlayerContext *CreatePlayersContext::localJson()
{
        auto ctx = new PlayersContext;
        ctx->setIOHandler(new FileJsonIO("Players"));
        ctx->setPersistDb(new SavePlayerModels);
        ctx->setFetchDb(new LoadPlayerModels);
        ctx->setDbCtx(new PlayersDbContext);
        ctx->setGetPlayerModelsFromDb(new GetPlayersFromDb);
        ctx->setJsonBuilder(new PlaJsonBuilder);
        ctx->setPlayerBuilder(new PlaBuilder);
        ctx->setDupChk(new DuplicateChecker);
        ctx->fetchDb()->fetch(ctx->dbCtx(),ctx->playerBuilder(),ctx->ioHandler());
        return ctx;
}
