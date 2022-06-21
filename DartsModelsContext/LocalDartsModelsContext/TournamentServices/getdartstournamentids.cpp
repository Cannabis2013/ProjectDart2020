#include "getdartstournamentids.h"
#include <DartsModelsContext/Contracts/Db/idbcontext.h>
#include <DartsModelsContext/Contracts/Model/imodel.h>

QVector<QUuid> GetDartsIds::get(const QVector<int> &indexes, const IDbContext<BaseModel> *dbContext) const
{
        return modelsByIndexes(dbContext->models(),indexes);
}

QVector<QUuid> GetDartsIds::modelsByIndexes(const QVector<BaseModel *> &models, const QVector<int> &indexes) const
{
        QVector<QUuid> selectModels;
        for (const auto &index : indexes)
                selectModels << models.at(index)->id();
        return selectModels;
}
