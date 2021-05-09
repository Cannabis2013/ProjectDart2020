#include "dartsmodelsservicebuilder.h"


IDartsModelsService *DartsModelsServiceBuilder::buildModelsService() const
{
    auto dartsTournamentsJsonDb = DartsTournamentJSonDb::createInstance(new AssembleDartsTournamentsFromJsonArray,
                                                                        new AssembleJsonFromDartsTournamentModels);
    auto dartsPointDb = DartsPointDbService::createInstance(new AssembleSingleAttemptPointsFromJson,
                                                            new AssembleJsonArrayFromDartsPoints);

    auto dartsModelsService =
            DartsModelsService::createInstance()
            ->setTournamentsDbContext(dartsTournamentsJsonDb)
            ->setDartsPointsDb(dartsPointDb)
            ->setGetOrderedDartsPointsModels(new GetOrderedDartsPointsModels)
            ->setAssembleDartsPointIndexes(new AssembleDartsPointIndexesByDartsPointModel);
    return dartsModelsService;
}
