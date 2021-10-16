#ifndef GETDARTSINDEXESMODEL_H
#define GETDARTSINDEXESMODEL_H

#include "DartsModelsContext/IndexesDbServices/dartsindexes.h"
#include "DartsModelsContext/IndexesDbSLAs/igetdartsindexesmodel.h"
class GetDartsIndexesModel : public IGetDartsIndexesModel
{
public:
    virtual IModel<QUuid> *indexesModel(const QUuid &tournamentId, const IModelsDbContext *dbContext) const override
    {
        auto models = dbContext->models();
        for (const auto &model : models) {
            if(matchByTournamentId(model,tournamentId))
                return model;
        }
        return nullptr;
    }
private:
    bool matchByTournamentId(IModel<QUuid> *model, const QUuid &tournamentId) const
    {
        return dynamic_cast<DartsIndexes*>(model)->tournamentId() == tournamentId;
    }
};

#endif // GETDARTSINDEXESMODEL_H
