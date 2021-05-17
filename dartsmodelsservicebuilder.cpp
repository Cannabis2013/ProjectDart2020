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
            ->setGetOrderedDartsPointsModels(new GetOrderedDartsPointsModels)
            ->setAssembleDartsPointIndexes(new GetDartsPointIndexesByDartsPointModel)
            ->setGetOrderedDartsScoreModels(new GetOrderedDartsScoreModels)
            ->setGetScoreIndexesByTournamentId(new GetDartsScoreIndexesByModel)
            ->setCountScoresByTournamentAndHint(new CountScoresByTournamentAndHint)
            ->setGetScoreModelsByTournamentId(new GetDartsScoreModelsByTournamentId)
            ->setGetScoreModelsByPlayerId(new GetDartsScoreModelsByPlayerId)
            ->setGetScoreModelsByRoundIndex(new GetDartsScoreModelsByRoundIndex)
            ->setGetScoreModelsByHint(new GetDartsScoreModelsByHint)
            ->setDartsScoreModelHintService(new SetDartsModelHint)
            ->setGetTournamentByIndexService(new GetDartsTournamentByIndexService)
            ->setGetDartsTournamentByIdService(new GetDartsTournamentById)
            ->setGetDartsPointByIdService(new GetDartsPointModelById)
            ->setGetDartsPointByParametersService(new GetDartsPointByParameters)
            ->setDartsPointModelHintService(new DartsPointSetHintService)
            ->setGetDartsPointModelsByTournamentId(new GetDartsPointModelsByTournamentId)
            ->setGetDartsScoreByParametersService(new GetDartsScoreByParameters)
            ->setGetDartsScoreByIdService(new GetDartsScoreById)
            ->setDeleteTournamentsByIndexes(new DeleteTournamentsByIndexesService);
    return dartsModelsService;
}
