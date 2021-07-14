#include "getinputmodelsservice.h"

using namespace DartsModelsContext;

QVector<const IPlayerInput *> GetInputModelsService::inputModels(const QUuid &tournamentId,
                                                                 const IDartsInputDb *dbService) const
{
    const auto& models = dbService->models();
    auto tournamentInputs = getModels(tournamentId,models);
    return tournamentInputs;
}

QVector<const IPlayerInput *> GetInputModelsService::inputModels(const QUuid &tournamentId,
                                                                 const int &hint,
                                                                 const IDartsInputDb *dbService) const
{
    auto models = inputModels(tournamentId,dbService);
    auto tournamentInputs = getModels(tournamentId,models);
    auto inputsByHint = getModels(hint,tournamentInputs);
    return inputsByHint;
}

QVector<const IPlayerInput *> GetInputModelsService::getModels(const QUuid &tournamentId,
                                                               const QVector<const IPlayerInput *> &models) const
{
    QVector<const IPlayerInput*> list;
    for (const auto& model : models) {
        if(model->tournamentId() == tournamentId)
            list << model;
    }
    return list;
}

QVector<const IPlayerInput *> GetInputModelsService::getModels(const int &hint,
                                                               const QVector<const IPlayerInput*> &models) const
{
    QVector<const IPlayerInput*> list;
    for (const auto& model : models) {
        if(model->hint() == hint)
            list << model;
    }
    return list;
}
