#ifndef GETDARTSTOURNAMENTIDS_H
#define GETDARTSTOURNAMENTIDS_H
#include "DartsModelsContext/TournamentsSLAs/igettournamentids.h"
class GetDartsIds : public IGetDartsTournamentIds
{
public:
    virtual QVector<QUuid> get(const QVector<int> &indexes, const IModelsDbContext *dbContext) const override
    {
        return modelsByIndexes(dbContext->models(),indexes);
    }
private:
    QVector<QUuid> modelsByIndexes(const QVector<IModel<QUuid>*> &models, const QVector<int> &indexes) const
    {
        QVector<QUuid> selectModels;
        for (const auto &index : indexes)
            selectModels << models.at(index)->id();
        return selectModels;
    }
};

#endif // GETDARTSTOURNAMENTIDS_H
