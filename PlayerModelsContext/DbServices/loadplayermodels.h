#ifndef LOADPLAYERMODELS_H
#define LOADPLAYERMODELS_H
#include "PlayerModelsContext/DbSLAs/IPlayersDbContext.h"
#include "PlayerModelsContext/DbSLAs/iplayer.h"
#include "DartsModelsContext/DbSLAs/abstractloadmodels.h"
#include "PlayerModelsContext/DbSLAs/iplayerbuilder.h"
#include "FileOperationsContext/SLAs/ifiledataio.h"
#include "PlayerModelsContext/DbSLAs/ifetchdb.h"
namespace LdPlaMds
{
    typedef IPlayersDbContext<IPlayer> DbCtx;
    typedef IFileDataIO<QByteArray> IODevice;
    typedef IPlayerBuilder<IPlayer,QByteArray> MdBuilder;
}
class LoadPlayerModels : public IFetchDb<LdPlaMds::DbCtx,LdPlaMds::IODevice,LdPlaMds::MdBuilder>
{
public:
    typedef IPlayer Model;
    virtual bool fetch(DbCtx *dbCtx, ModelBuilder *builder, IODevice *ioDevice) const override
    {
        auto json = ioDevice->read();
        QVector<Model*> models = builder->convert(json);
        fetchDb(models,dbCtx);
        return true;
    }
private:
    void fetchDb(const QVector<Model*> &models, DbCtx *dbCtx) const
    {
        for (const auto &model : models)
            dbCtx->add(model);
    }
};

#endif // LOADPLAYERMODELS_H
