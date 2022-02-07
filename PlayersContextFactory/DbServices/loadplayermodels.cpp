#include "loadplayermodels.h"
#include <QVector>
#include "DbSLAs/IPlayersDbContext.h"
#include "DbSLAs/iplayer.h"
#include "DbSLAs/iplayerbuilder.h"
#include "IOSLAs/ifiledataio.h"
bool LoadPlayerModels::fetch(DbCtx *dbCtx, ModelBuilder *builder, IODevice *ioDevice) const
{
    auto json = ioDevice->read();
    QVector<Model*> models = builder->convert(json);
    fetchDb(models,dbCtx);
    return true;
}
void LoadPlayerModels::fetchDb(const QVector<Model *> &models, DbCtx *dbCtx) const
{
    for (const auto &model : models)
        dbCtx->add(model);
}
