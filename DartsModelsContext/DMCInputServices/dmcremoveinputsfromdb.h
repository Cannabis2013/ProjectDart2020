#ifndef DMCREMOVEINPUTSFROMDB_H
#define DMCREMOVEINPUTSFROMDB_H

#include "DartsModelsContext/DMCInputSLAs/iplayerinput.h"
#include "DartsModelsContext/DMCInputSLAs/iremovedartsinputsfromdb.h"

class DMCRemoveInputsFromDb : public IRemoveDartsInputsFromDb
{
public:
    void remove(const QVector<const IModel<QUuid>*> &models,
                const int &hint,
                IModelsDbContext *dbService) const override
    {
        for (const auto model : qAsConst(models))
            removeModel(model,hint,dbService);
    }
    void remove(const QVector<const IModel<QUuid>*> &models,
                const QUuid &tournamentId,
                IModelsDbContext *dbService) const override
    {
        for (const auto& model : models) {
            auto inputModel = dynamic_cast<const IPlayerInput*>(model);
            if(inputModel->tournamentId() == tournamentId)
                remove(model->id(),dbService);
        }
    }
    void remove(const QUuid &id,
                IModelsDbContext* dbService) const override
    {
        auto models = dbService->models();
        for (const auto &model : models)
            removeModel(model,id,dbService);
    }
private:
    void removeModel(const IModel<QUuid> *model, const int &hint, IModelsDbContext *dbService) const
    {
        auto inputModel = dynamic_cast<const IPlayerInput*>(model);
        if(inputModel->hint() == hint)
            remove(inputModel->id(),dbService);
    }
    bool removeModel(const IModel<QUuid> *inputModel, const QUuid &id, IModelsDbContext *dbService) const
    {
        if(inputModel->id() == id)
            return dbService->remove(dbService->indexOf(inputModel));
        return false;
    }
};
#endif // DEFAULTDBMANIPULATORSERVICE_H
