#include "dartsmodelsservicebuilder.h"


IDartsModelsService *DartsModelsServiceBuilder::buildModelsService() const
{
    auto dartsTournamentsJsonDb = DartsTournamentJSonDb::createInstance(new AssembleDartsTournamentsFromJsonArray,
                                                                        new AssembleJsonFromDartsTournamentModels);
    auto dartsPointDb = DartsPointJsonDbService::createInstance(new AssembleSingleAttemptPointsFromJson,
                                                            new AssembleJsonArrayFromDartsPoints);
    auto dartsScoreDb = DartsScoreJsonDb::createInstance(new AssembleMultiAttemptScoresByJson,
                                                         new AssembleJsonByDartsScoreModels);
    auto dartsModelsService =
            DartsModelsService::createInstance()
            ->setTournamentsDbContext(dartsTournamentsJsonDb)
            ->setDartsPointsDb(dartsPointDb)
            ->setDartsScoreDb(dartsScoreDb)
            ->setAssembleDartsPointIndexes(new GetDartsPointIndexesByDartsPointModel)
            ->setGetOrderedDartsScoreModels(new SortPlayerInputsByPredicate)
            ->setGetScoreIndexesByTournamentId(new GetDartsScoreIndexesByModel)
            ->setGetTournamentByIndexService(new GetDartsTournamentByIndexService)
            ->setGetDartsTournamentByIdService(new GetDartsTournamentById)
            ->setGetDartsInputModelByIdService(new GetDartsInputModelById)
            ->setDartsPointModelHintService(new SetDartsInputHintService)
            ->setDeleteTournamentsByIndexes(new DeleteTournamentsByIndexesService)
            ->setRemoveModelsService(new RemoveModelsFromDbContext)
            ->setDartsPointLessThanPredicate(new DartsPointLessThanPredicate)
            ->setDartsScoreLessThanPredicate(new DartsScoreLessThanPredicate)
            ->setDartsInputsFilterService(new DartsInputsFilterService);
    return dartsModelsService;
}
