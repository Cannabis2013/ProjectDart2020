#include "createplayerscontext.h"
#include "ModelsServices/duplicatechecker.h"
#include "DbServices/saveplayermodels.h"
#include "DbServices/loadplayermodels.h"
#include "DataServices/plajsonbuilder.h"
#include "playerscontext.h"
#include "IOServices/filejsonio.h"
#include "DbServices/playersdbcontext.h"
#include "Services/getplayersfromdb.h"
#include "Services/plabuilder.h"
AbsPlaCtx *CreatePlayersContext::localJson()
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
