#ifndef GETDARTSTOURNAMENTFROMDB_H
#define GETDARTSTOURNAMENTFROMDB_H

#include "DartsModelsContext/DMCTournamentSLAs/igetdartstournamentfromdb.h"

class GetDartsTournamentFromDb : public IGetDartsTournamentFromDb
{
public:
    virtual const IModel<QUuid> *tournament(const QUuid &tournamentId, const IModelsDbContext *dbService) const override
    {
        auto models = dbService->models();
        auto model = getModelById(models,tournamentId);
        return model;
    }
private:
    const IModel<QUuid> *getModelById(const QVector<const IModel<QUuid>*> &models,const QUuid &tournamentId) const
    {
        for (const auto &model : models) {
            if(model->id() == tournamentId)
                return model;
        }
        throw "Model not found";
    }
};

#endif // GETDARTSTOURNAMENTDATA_H
