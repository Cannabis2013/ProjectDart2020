#include "getinputmodelsservice.h"

using namespace DartsModelsContext;

QVector<const IPlayerInput *> GetInputModelsService::inputModels(const QUuid &tournamentId, const IDartsInputDb *dbService) const
{
    QVector<const IPlayerInput*> list;
    const auto& models = dbService->models();
    for (const auto& model : models) {
        if(model->tournamentId() == tournamentId)
            list << model;
    }
    return list;
}

QVector<const IPlayerInput *> GetInputModelsService::inputModels(const QUuid &tournamentId, const int &hint, const IDartsInputDb *dbService) const
{
    QVector<const IPlayerInput*> list;
    auto models = inputModels(tournamentId,dbService);
    for (const auto& model : models){
        if(model->hint() == hint)
            list << model;
    }
    return list;
}
