#include "dartsjsonservicebuilder.h"


IDartsJsonService *DartsJsonServiceBuilder::buildModelsService() const
{
    auto jsonModelsService = DartsJsonService::createInstance()
            ->setAssembleJsonDartsPointIndexes(new AssembleJsonFromDartsPointIndexes)
            ->setGetPlayerIndexesFromJson(new GetPlayerIndexesFromJson)
            ->setAssembleJsonFromPlayerNamesAndIds(new JsonArrayFromPlayerNamesAndIds)
            ->setAssembleJsonFromTournamentDartsPoints(new AssembleJsonFromDartsPoints())
            ->setAssembleJsonOrderedDartsPointModels(new AssembleJsonFromOrderedDartsPointModels)
            ->setAssembleDartsTournamentFromJson(new AssembleDartsTournamentModelFromJson)
            ->setAssembleJsonDartsTournamentModels(new AssembleJsonDartsTournamentModels)
            ->setAssembleJsonFromPlayerIdAndName(new AssembleJsonFromPlayerNameAndId)
            ->setAssembleJSonFromDartsTournamentModel(new AssembleJsonBasicTournamentValues)
            ->setGetDeleteTournamentIndexesFromJson(new GetTournamentIndexesFromJson)
            ->setGetDeletePlayerIndexFromJson(new GetDeletePlayerIndexFromJson)
            ->setAssembleDartsPointModelFromJson(new AssembleDartsPointModelFromJson)
            ->setAssemblePlayerModelFromJson(new AssemblePlayerModelFromJson)
            ->setAssignPlayerIdsToDartsTournament(new AssignPlayerIdsToDartsTournamentModel)
            ->setAddPlayerNamesToTournamentJson(new AddPlayerNamesToDartsTournamentJson)
            ->setAssembleJsonFromDartsMultiAttemptScores(new AssembleJsonFromDartsMultiAttemptScores)
            ->setAssembleJsonByDartsScoreIndexes(new AssembleJsonByDartsScoreIndexes)
            ->setGetPlayerNameById(new GetPlayerNameById)
            ->setGetWinnerIdByJson(new GetWinnerIdByJson)
            ->setGetTournamentIdByJson(new GetTournamentIdByJson)
            ->setAddWinnerNameToDartsTournamentJson(new AddWinnerNameToTournamentJson);
    return jsonModelsService;
}
