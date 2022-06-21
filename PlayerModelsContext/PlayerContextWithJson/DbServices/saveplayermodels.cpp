#include "saveplayermodels.h"
#include <qbytearray.h>
#include <qvector.h>
#include <DartsModelsContext/Contracts/Db/ifiledataio.h>
#include <PlayerModelsContext/Contracts/DbSLAs/IPlayersDbContext.h>
#include <PlayerModelsContext/Contracts/DataSLAs/ijsonbuilder.h>

bool SavePlayerModels::save(DbCtx *dbCtx, IODevice *ioDevice, DataManCtx *dataAdder)
{
        auto data = ioDevice->read();
        auto models = dbCtx->models();
        dataAdder->create(models,data);
        return ioDevice->save(data);
}

