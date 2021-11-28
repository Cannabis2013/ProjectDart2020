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
class CreatePlayersContext
{
public:
    static PlayersContext *localJson()
    {
        auto ctx = new PlayersContext;
        auto ioDevice = new FileJsonIO("Players");
        ctx->setPersistDbCtx(new SaveToStorage(ioDevice));
        ctx->setLoadFromStorage(new LoadFromStorage(ioDevice));
        ctx->setDbContext(new PlayersDbContext);
        ctx->setGetPlayerModelsFromDb(new GetPlayersFromDb);
        ctx->setJsonBuilder(new PlayerJsonBuilder);
        ctx->setPlayerBuilder(new PlayerBuilder);
        ctx->loadFromStorage()->load(ctx->dbContext(),ctx->playerBuilder());
        return ctx;
    }
};
#endif // LOCALPLAYERSCONTEXT_H
