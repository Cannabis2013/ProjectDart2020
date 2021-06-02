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
            ->setGetTournamentByIndexService(new GetDartsTournamentByIndexService)
            ->setGetDartsTournamentByIdService(new GetDartsTournamentById)
            ->setDeleteTournamentsByIndexes(new DeleteTournamentsByIndexesService)
            ->setAssignPlayerIdsToDartsTournament(new AssignPlayerIdsToDartsTournamentModel);
    return dartsModelsService;
}
