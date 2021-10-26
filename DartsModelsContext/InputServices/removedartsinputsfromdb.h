#ifndef REMOVEDARTSINPUTSFROMDB_H
#define REMOVEDARTSINPUTSFROMDB_H

#include "DartsModelsContext/InputModelsSLAs/iplayerinput.h"
#include "DartsModelsContext/InputsDbSLAs/iremovedartsinputsfromdb.h"

class RemoveDartsInputsFromDb : public IRemoveDartsInputsFromDb
{
public:
    IDartsInputsDbContext *removeInputsById(const QUuid &id, IDartsInputsDbContext* dbService) const override
    {
        auto models = dbService->models();
        for (const auto &model : models)
            removeModel(model,id,dbService);
        return dbService;
    }
    IDartsInputsDbContext *removeInputsByTournamentId(const QUuid &tournamentId, IDartsInputsDbContext *dbService) const override
    {
        auto models = dbService->models();
        for (const auto& model : models) {
            auto inputModel = dynamic_cast<IPlayerInput*>(model);
            if(inputModel->tournamentId() == tournamentId)
                removeModel(model,model->id(),dbService);
        }
        return dbService;
    }
    IDartsInputsDbContext *removeByHint(const QUuid &tournamentId, const int &hint, IDartsInputsDbContext *dbService) const override
    {
        auto models = dbService->models();
        for (const auto model : qAsConst(models))
            removeModel(model,tournamentId,hint,dbService);
        return dbService;
    }
    IDartsInputsDbContext *removeByTournamentIds(const QVector<QUuid> &tournamentIds, IDartsInputsDbContext *dbService) const override
    {
        for (const auto &tournamentId : tournamentIds)
            removeInputsByTournamentId(tournamentId,dbService);
        return dbService;
    }
private:
    void removeModel(IModel<QUuid> *model, const QUuid &tournamentId, const int &hint, IDartsInputsDbContext *dbService) const
    {
        auto input = dynamic_cast<const IPlayerInput*>(model);
        if(input->hint() == hint && input->tournamentId() == tournamentId)
            removeModel(model,input->id(),dbService);
    }
    bool removeModel(IModel<QUuid> *inputModel, const QUuid &id, IModelsDbContext *dbService) const
    {
        if(inputModel->id() == id)
            return dbService->remove(dbService->indexOf(inputModel));
        return false;
    }
};
#endif // DEFAULTDBMANIPULATORSERVICE_H
