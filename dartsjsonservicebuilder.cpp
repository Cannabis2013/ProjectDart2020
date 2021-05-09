#include "dartsjsonservicebuilder.h"


IDartsJsonService *DartsJsonServiceBuilder::buildModelsService() const
{
    auto jsonModelsService = DartsModelsJsonService::createInstance()
            ->setAssembleJsonDartsIndexes(new AssembleJsonFromDartsPointIndexes)
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
            ->setAssembleJsonDartsTournamentModel(new AssembleJsonFromDartsTournament)
            ->setAddPlayerNameToJsonPointModel(new AddPlayerNameToJsonPointModel)
            ->setAssembleJsonFromDartsPointModel(new AssembleJsonFromDartsPointModel);
    return jsonModelsService;
}
