#include "removeinputsfromdb.h"

void ModelsContext::RemoveInputsFromDb::remove(const QVector<const IModel<QUuid> *> &models,
                                               const int &hint, IDbService *dbService) const
{
    for (const auto model : qAsConst(models))
        removeModel(model,hint,dbService);
}


void ModelsContext::RemoveInputsFromDb::remove(const QUuid &id, IDbService *dbService) const
{
    auto models = dbService->models();
    for (const auto &model : models)
        removeModel(model,id,dbService);
}

void ModelsContext::RemoveInputsFromDb::remove(const QVector<const IModel<QUuid> *> &models,
                                               const QUuid &tournamentId,
                                               IDbService *dbService) const
{
    for (const auto& model : models) {
        auto inputModel = dynamic_cast<const IPlayerInput*>(model);
        if(inputModel->tournamentId() == tournamentId)
            remove(model->id(),dbService);
    }
}

void ModelsContext::RemoveInputsFromDb::removeModel(const IModel<QUuid> *model,const int &hint,
                                                    IDbService *dbService) const
{
    auto inputModel = dynamic_cast<const IPlayerInput*>(model);
    if(inputModel->hint() == hint)
        remove(inputModel->id(),dbService);
}

bool ModelsContext::RemoveInputsFromDb::removeModel(const IModel<QUuid> *inputModel,const QUuid &id,
                                                    IDbService *dbService) const
{
    if(inputModel->id() == id)
        return dbService->remove(dbService->indexOf(inputModel));
    return false;
}
