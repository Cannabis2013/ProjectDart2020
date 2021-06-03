#include "getinputmodelsservice.h"

using namespace DartsModelsContext;

GetInputModelsService::InputModels DartsModelsContext::GetInputModelsService::inputModelsByTournamentId(const IdFormat &tournamentId,
                                                                                                        const DbServiceInterface *dbService) const
{
    QVector<const IPlayerInput*> list;
    auto models = dbService->models();
    for (const auto& model : models) {
        if(model->tournamentId() == tournamentId)
            models << model;
    }
    return list;
}

GetInputModelsService::InputModels DartsModelsContext::GetInputModelsService::inputModelsByHint(const IdFormat &tournamentId,
                                                                                                const int &hint,
                                                                                                const DbServiceInterface *dbService) const
{
    QVector<const IPlayerInput*> list;
    auto models = inputModelsByTournamentId(tournamentId,dbService);
    for (const auto& model : models){
        if(model->hint() == hint)
            list << model;
    }
    return list;
}
