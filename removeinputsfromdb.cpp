#include "removeinputsfromdb.h"

void DartsModelsContext::RemoveInputsFromDb::remove(const QVector<const IPlayerInput*> &models,
                                                    const int &hint,IDartsInputDb *dbService) const
{
    for (const auto model : qAsConst(models))
        removeModel(model,hint,dbService);
}


void DartsModelsContext::RemoveInputsFromDb::remove(const QUuid &id, IDartsInputDb *dbService) const
{
    auto models = dbService->models();
    for (const auto &model : models)
        removeModel(model,id,dbService);
}

void DartsModelsContext::RemoveInputsFromDb::remove(const QVector<const IPlayerInput*> &models,const QUuid &tournamentId,
                                                    IDartsInputDb *dbService) const
{
    for (const auto& model : models) {
        if(model->tournamentId() == tournamentId)
            remove(model->id(),dbService);
    }
}

void DartsModelsContext::RemoveInputsFromDb::removeModel(const IPlayerInput *inputModel,const int &hint,
                                                         IDartsInputDb *dbService) const
{
    if(inputModel->hint() == hint)
        remove(inputModel->id(),dbService);
}

bool DartsModelsContext::RemoveInputsFromDb::removeModel(const IPlayerInput *inputModel,
                                                         const QUuid &id, IDartsInputDb *dbService) const
{
    if(inputModel->id() == id)
        return dbService->remove(dbService->indexOf(inputModel));
    return false;
}
