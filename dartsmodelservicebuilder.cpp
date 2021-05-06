#include "dartsmodelservicebuilder.h"


IDartsModelsService *DartsModelServiceBuilder::buildModelsService() const
{
    auto dartsModelsService =
            DartsModelsService::createInstance()
            ->setTournamentsDbContext(new DartsTournamentJSonDb)
            ->setDartsPointsDb(new DartsPointDbService)
            ->setAssembleDartsTournamentFromJson(new AssembleDartsTournamentModelFromJson)
            ->setGetOrderedDartsPointsModels(new GetOrderedDartsPointsModels)
            ->setGetDartsPointIndexes(new AssembleDartsPointIndexesByDartsPointModel);
    return dartsModelsService;
}
