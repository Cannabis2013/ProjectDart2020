#include "dartsmodelservicebuilder.h"


IDartsModelsService *DartsModelServiceBuilder::buildModelsService() const
{
    auto dartsPointDb = DartsPointDbService::createInstance()
            ->setDartsPointsExtractorService(new AssembleSingleAttemptPointsFromJson)
            ->setDartsPointsJsonAssemblerService(new AssembleJsonArrayFromDartsPoints);
    auto dartsModelsService =
            DartsModelsService::createInstance()
            ->setTournamentsDbContext(new DartsTournamentJSonDb)
            ->setDartsPointsDb(dartsPointDb)
            ->setGetOrderedDartsPointsModels(new GetOrderedDartsPointsModels)
            ->setGetDartsPointIndexes(new AssembleDartsPointIndexesByDartsPointModel);
    return dartsModelsService;
}
