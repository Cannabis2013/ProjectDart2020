#ifndef LOADPLAYERMODELS_H
#define LOADPLAYERMODELS_H

#include <DartsModelsContext/Contracts/Db/ifiledataio.h>
#include <PlayerModelsContext/Contracts/DbSLAs/IPlayersDbContext.h>
#include <PlayerModelsContext/Contracts/DbSLAs/ifetchdb.h>
#include <PlayerModelsContext/Contracts/DbSLAs/iplayer.h>
#include <PlayerModelsContext/Contracts/DbSLAs/iplayerbuilder.h>

namespace LdPlaMds
{
    typedef IPlayersDbContext<IPlayer> DbCtx;
    typedef IFileDataIO IODevice;
    typedef IPlayerBuilder<IPlayer,QByteArray> MdBuilder;
}

class LoadPlayerModels : public IFetchDb<LdPlaMds::DbCtx,LdPlaMds::IODevice,LdPlaMds::MdBuilder>
{
public:
    typedef IPlayer Model;
    virtual bool fetch(DbCtx *dbCtx, ModelBuilder *builder, IODevice *ioDevice) const override;
private:
    void fetchDb(const QVector<Model*> &models, DbCtx *dbCtx) const;
};

#endif // LOADPLAYERMODELS_H
