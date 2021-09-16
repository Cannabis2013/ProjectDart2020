#include "removeinputsfromdb.h"

void RemoveInputsFromDb::remove(const QVector<const IModel<QUuid> *> &models,
                                               const int &hint, IModelsDbContext *dbService) const
{
    for (const auto model : qAsConst(models))
        removeModel(model,hint,dbService);
}


void RemoveInputsFromDb::remove(const QUuid &id, IModelsDbContext *dbService) const
{
    auto models = dbService->models();
    for (const auto &model : models)
        removeModel(model,id,dbService);
}

void RemoveInputsFromDb::remove(const QVector<const IModel<QUuid> *> &models,
                                               const QUuid &tournamentId,
                                               IModelsDbContext *dbService) const
{
    for (const auto& model : models) {
        auto inputModel = dynamic_cast<const IPlayerInput*>(model);
        if(inputModel->tournamentId() == tournamentId)
            remove(model->id(),dbService);
    }
}

void RemoveInputsFromDb::removeModel(const IModel<QUuid> *model,const int &hint,
                                     IModelsDbContext *dbService) const
{
    auto inputModel = dynamic_cast<const IPlayerInput*>(model);
    if(inputModel->hint() == hint)
        remove(inputModel->id(),dbService);
}

bool RemoveInputsFromDb::removeModel(const IModel<QUuid> *inputModel,const QUuid &id,
                                     IModelsDbContext *dbService) const
{
    if(inputModel->id() == id)
        return dbService->remove(dbService->indexOf(inputModel));
    return false;
}
