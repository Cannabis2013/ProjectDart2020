#include "dartsmodelservicebuilder.h"


IDartsModelsService *DartsModelServiceBuilder::buildModelsService() const
{
    auto dartsTournamentsJsonDb = DartsTournamentJSonDb::createInstance(new AssembleDartsTournamentsFromJsonArray,
                                                                        new AssembleJsonFromDartsTournamentModels);
    auto dartsPointDb = DartsPointDbService::createInstance()
            ->setDartsPointsExtractorService(new AssembleSingleAttemptPointsFromJson)
            ->setDartsPointsJsonAssemblerService(new AssembleJsonArrayFromDartsPoints);
    auto dartsModelsService =
            DartsModelsService::createInstance()
            ->setTournamentsDbContext(dartsTournamentsJsonDb)
            ->setDartsPointsDb(dartsPointDb)
            ->setGetOrderedDartsPointsModels(new GetOrderedDartsPointsModels)
            ->setAssembleDartsPointIndexes(new AssembleDartsPointIndexesByDartsPointModel);
    return dartsModelsService;
}
