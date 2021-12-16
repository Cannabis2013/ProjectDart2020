#ifndef CreatePlayersContext_H
#define CreatePlayersContext_H
#include "PlayerModelsContext/playerscontext.h"
#include "PlayerModelsContext/Services/getplayersfromdb.h"
#include "PlayerModelsContext/DbServices/playersdbcontext.h"
#include "FileOperationsContext/Services/filejsonio.h"
#include "PlayerModelsContext/Services/plabuilder.h"
#include "DartsModelsContext/DbServices/persistdbctx.h"
#include "PlayerModelsContext/ModelsServices/duplicatechecker.h"
#include "PlayerModelsContext/DbServices/saveplayermodels.h"
#include "PlayerModelsContext/DbServices/loadplayermodels.h"
#include "PlayerModelsContext/DataServices/plajsonbuilder.h"
class CreatePlayersContext
{
public:
    static PlayersContext *localJson()
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
};
#endif // LOCALPLAYERSCONTEXT_H
