#include "saveplayermodels.h"
#include <qbytearray.h>
#include "DbSLAs/iplayer.h"
#include "DbSLAs/IPlayersDbContext.h"
#include "DataSLAs/idatabuilder.h"
#include "IOSLAs/ifiledataio.h"
#include "DbSLAs/iplayer.h"
#include <qvector.h>
bool SavePlayerModels::save(DbCtx *dbCtx, IODevice *ioDevice, DataManCtx *dataAdder)
{
    auto data = ioDevice->read();
    auto models = dbCtx->models();
    dataAdder->create(models,data);
    return ioDevice->save(data);
}

