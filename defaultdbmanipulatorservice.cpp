#include "defaultdbmanipulatorservice.h"



void DartsModelsContext::DefaultDbManipulatorService::removeModelsByHint(const ModelInterfaces &models, const int &hint, DbServiceInterface *dbService) const
{
    for (const auto model : qAsConst(models))
    {
        if(model->hint() == hint)
        {
            removeModelById(model->id(),dbService);
            return;
        }
    }
}


void DartsModelsContext::DefaultDbManipulatorService::removeModelById(const IdFormat &id,
                                                                      DbServiceInterface *dbService) const
{
    auto models = dbService->models();
    for (int i = 0; i < models.count(); ++i) {
        auto model = models.at(i);
        if(model->id() == id)
        {
            dbService->remove(i);
            return;
        }
    }
}


void DartsModelsContext::DefaultDbManipulatorService::removeModelsByTournamentId(const ModelInterfaces &models,
                                                                                 const IdFormat &tournamentId,
                                                                                 DbServiceInterface *dbService) const
{
    for (const auto& model : models) {
        if(model->tournamentId() == tournamentId)
            removeModelById(model->id(),dbService);
    }
}
