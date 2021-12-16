#ifndef REMOVEDARTSINPUTS_H
#define REMOVEDARTSINPUTS_H
#include <qvector.h>
#include "DartsModelsContext/InputModelsSLAs/iplayerinput.h"
#include "DartsModelsContext/InputsDbSLAs/iremovedartsinputs.h"
class RemoveDartsInputs : public IRemoveDartsInputs<IModel<QUuid>,QUuid,IDbContext<IModel<QUuid>>>
{
public:
    IDbContext<Model> *removeInputsById(const QUuid &id, IDbContext<Model>* dbService) const override
    {
        auto models = dbService->models();
        for (const auto &model : models)
            removeModel(model,id,dbService);
        return dbService;
    }
    IDbContext<Model> *removeInputsByTournamentId(const QUuid &tournamentId, IDbContext<Model> *dbService) const override
    {
        auto models = dbService->models();
        for (const auto& model : models) {
            auto inputModel = dynamic_cast<IPlayerInput*>(model);
            if(inputModel->tournamentId() == tournamentId)
                removeModel(model,model->id(),dbService);
        }
        return dbService;
    }
    IDbContext<Model> *removeByHint(const QUuid &tournamentId, const int &hint, IDbContext<Model> *dbService) const override
    {
        auto models = dbService->models();
        for (const auto model : qAsConst(models))
            removeModel(model,tournamentId,hint,dbService);
        return dbService;
    }
    IDbContext<Model> *removeByTournamentIds(const QVector<QUuid> &tournamentIds, IDbContext<Model> *dbService) const override
    {
        for (const auto &tournamentId : tournamentIds)
            removeInputsByTournamentId(tournamentId,dbService);
        return dbService;
    }
private:
    void removeModel(IModel<QUuid> *model, const QUuid &tournamentId, const int &hint, IDbContext<Model> *dbService) const
    {
        auto input = dynamic_cast<const IPlayerInput*>(model);
        if(input->hint() == hint && input->tournamentId() == tournamentId)
            removeModel(model,input->id(),dbService);
    }
    bool removeModel(IModel<QUuid> *inputModel, const QUuid &id, IDbContext<Model> *dbService) const
    {
        if(inputModel->id() == id)
        {
            dbService->remove(dbService->indexOf(inputModel));
            return true;
        }
        return false;
    }
};
#endif // DEFAULTDBMANIPULATORSERVICE_H
