#ifndef GETDARTSTOURNAMENTIDS_H
#define GETDARTSTOURNAMENTIDS_H
#include "TournamentsSLAs/igettournamentids.h"
#include "ModelSLAs/imodel.h"
#include "DbSLAs/idbcontext.h"
#include <quuid.h>
#include <qvector.h>
class GetDartsIds : public IGetDartsTournamentIds<IModel<QUuid>,IDbContext<IModel<QUuid>>>
{
public:
    virtual QVector<QUuid> get(const QVector<int> &indexes, const IDbContext<BaseModel> *dbContext) const override
    {
        return modelsByIndexes(dbContext->models(),indexes);
    }
private:
    QVector<QUuid> modelsByIndexes(const QVector<BaseModel*> &models, const QVector<int> &indexes) const
    {
        QVector<QUuid> selectModels;
        for (const auto &index : indexes)
            selectModels << models.at(index)->id();
        return selectModels;
    }
};

#endif // GETDARTSTOURNAMENTIDS_H
