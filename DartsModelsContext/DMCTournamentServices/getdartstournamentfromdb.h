#ifndef GETDARTSTOURNAMENTFROMDB_H
#define GETDARTSTOURNAMENTFROMDB_H

#include "DartsModelsContext/TournamentsDbSLAs/igetdartstournamentfromdb.h"

class GetDartsTournamentFromDb : public IGetDartsTournamentFromDb
{
public:
    virtual IModel<QUuid> *tournament(const QUuid &tournamentId, const IModelsDbContext *dbService) const override
    {
        auto models = dbService->models();
        auto model = getModelById(models,tournamentId);
        return model;
    }
private:
    IModel<QUuid> *getModelById(const QVector<IModel<QUuid>*> &models,const QUuid &tournamentId) const
    {
        for (const auto &model : models) {
            if(model->id() == tournamentId)
                return model;
        }
        throw "Model not found";
    }
};

#endif // GETDARTSTOURNAMENTDATA_H
