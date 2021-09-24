#ifndef GETDARTSTOURNAMENTFROMDB_H
#define GETDARTSTOURNAMENTFROMDB_H

#include "DartsModelsContext/DMCTournamentSLAs/igetdartstournamentfromdb.h"

class GetDartsTournamentFromDb : public IGetDartsTournamentFromDb
{
public:
    virtual const Tournament *tournament(const Id &tournamentId, const DbService *dbService) const override
    {
        auto models = dbService->models();
        auto model = getModelById(models,tournamentId);
        return model;
    }
private:
    const Tournament *getModelById(const QVector<const Tournament*> &models,const Id &tournamentId) const
    {
        for (const auto &model : models) {
            if(model->id() == tournamentId)
                return model;
        }
        throw "Model not found";
    }
};

#endif // GETDARTSTOURNAMENTDATA_H
