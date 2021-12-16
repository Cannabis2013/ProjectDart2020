#ifndef SAVEPLAYERMODELS_H
#define SAVEPLAYERMODELS_H
#include "DartsModelsContext/DbSLAs/abstractsavetostorage.h"
#include "PlayerModelsContext/DbSLAs/IPlayersDbContext.h"
#include "PlayerModelsContext/DbSLAs/iplayer.h"
#include "isaveplayers.h"
#include "FileOperationsContext/SLAs/ifiledataio.h"
#include <PlayerModelsContext/DataSLAs/idatabuilder.h>

namespace SvPlaCtx{
    typedef IPlayer Model;
    typedef QByteArray Json;
    typedef IPlayersDbContext<Model> DbCtx;
    typedef IFileDataIO<QByteArray> FileDataIO;
    typedef IDataBuilder<Model,Json> DataAdder;
}

class SavePlayerModels : public ISavePlayers<SvPlaCtx::FileDataIO,
        SvPlaCtx::DbCtx,SvPlaCtx::DataAdder>
{
public:
    virtual bool save(DbCtx *dbCtx, IODevice *ioDevice, DataManCtx *dataAdder) override
    {
        auto data = ioDevice->read();
        auto models = dbCtx->models();
        dataAdder->create(models,data);
        return ioDevice->save(data);
    }
};
#endif // SAVEPLAYERMODELS_H
