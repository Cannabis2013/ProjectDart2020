#ifndef CreatePlayersContext_H
#define CreatePlayersContext_H
#include "PlayerModelsContext/playerscontext.h"
#include "PlayerModelsContext/Services/getplayersfromdb.h"
#include "PlayerModelsContext/DbServices/playersdbcontext.h"
#include "FileOperationsContext/Services/filejsonio.h"
#include "PlayerModelsContext/Services/playerjsonbuilder.h"
#include "PlayerModelsContext/Services/playerbuilder.h"
#include "ModelsContext/DbServices/persistdbctx.h"
#include "ModelsContext/DbServices/loadfromstorage.h"
#include "PlayerModelsContext/ModelsServices/duplicatechecker.h"
class CreatePlayersContext
{
public:
    static PlayersContext *localJson()
    {
        auto ctx = new PlayersContext;
        auto ioDevice = new FileJsonIO("Players");
        ctx->setPersistDbCtx(new SaveToStorage(ioDevice));
        ctx->setLoadFromStorage(new LoadFromStorage(ioDevice));
        ctx->setDbCtx(new PlayersDbContext);
        ctx->setGetPlayerModelsFromDb(new GetPlayersFromDb);
        ctx->setJsonBuilder(new PlayerJsonBuilder);
        ctx->setPlayerBuilder(new PlayerBuilder);
        ctx->loadFromStorage()->load(ctx->dbCtx(),ctx->playerBuilder());
        ctx->setDupChk(new DuplicateChecker);
        return ctx;
    }
};
#endif // LOCALPLAYERSCONTEXT_H
