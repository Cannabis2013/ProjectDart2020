#include "getinputmodelsservice.h"

using namespace ModelsContext;

QVector<const IModel<QUuid>*> GetInputModelsService::inputModels(const QUuid &tournamentId,
                                                                 const IDbService *dbService) const
{
    const auto& models = dbService->models();
    auto tournamentInputs = getModels(tournamentId,models);
    return tournamentInputs;
}

QVector<const IModel<QUuid>*> GetInputModelsService::inputModels(const QUuid &tournamentId,
                                                                 const int &hint,
                                                                 const IDbService *dbService) const
{
    auto models = inputModels(tournamentId,dbService);
    auto tournamentInputs = getModels(tournamentId,models);
    auto inputsByHint = getModels(hint,tournamentInputs);
    return inputsByHint;
}

QVector<const IModel<QUuid>*> GetInputModelsService::getModels(const QUuid &tournamentId,
                                                               const QVector<const IModel<QUuid>*> &models) const
{
    QVector<const IModel<QUuid>*> list;
    for (const auto& model : models) {
        auto inputModel = dynamic_cast<const IPlayerInput*>(model);
        if(inputModel->tournamentId() == tournamentId)
            list << model;
    }
    return list;
}

QVector<const IModel<QUuid>*> GetInputModelsService::getModels(const int &hint,
                                                               const QVector<const IModel<QUuid>*> &models) const
{
    QVector<const IModel<QUuid>*> list;
    for (const auto& model : models) {
        auto inputModel = dynamic_cast<const IPlayerInput*>(model);
        if(inputModel->hint() == hint)
            list << model;
    }
    return list;
}
