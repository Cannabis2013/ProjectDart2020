#include "dartsjsonservicebuilder.h"

using namespace DartsModelsContext;

DartsModelsContext::IDartsJsonService *DartsModelsContext::DartsJsonServiceBuilder::buildDartsJsonService() const
{
    auto service = DartsJsonService::createInstance()
            ->setAssembleDartsTournamentFromJson(new AssembleDartsTournamentModelFromJson)
            ->setAssembleJsonDartsTournamentModels(new AssembleJsonDartsTournamentModels)
            ->setAssembleJSonFromDartsTournamentModel(new AssembleJsonBasicTournamentValues)
            ->setGetDeleteTournamentIndexesFromJson(new GetTournamentIndexesFromJson)
            ->setAssignPlayerIdsToDartsTournament(new AssignPlayerIdsToDartsTournamentModel)
            ->setAddPlayerNamesToTournamentJson(new AddPlayerNamesToDartsTournamentJson)
            ->setGetTournamentIdByJson(new GetTournamentIdByJson)
            ->setAddWinnerNameToDartsTournamentJson(new AddWinnerNameToTournamentJson);
    return service;
}

DartsJsonServiceBuilder::PointsJsonService *DartsModelsContext::DartsJsonServiceBuilder::buildDartsPointsJsonService() const
{
    auto service = DartsPointsJsonService::createInstance()
            ->setAssembleJsonDartsPointIndexes(new AssembleJsonFromDartsPointIndexes)
            ->setAssembleJsonFromTournamentDartsPoints(new AssembleJsonFromDartsPoints)
            ->setAssembleJsonOrderedDartsPointModels(new AssembleJsonFromOrderedDartsPointModels);
    return service;
}

IDartsJsonServiceBuilder::ScoreJsonService *DartsJsonServiceBuilder::buildDartsScoreJsonService() const
{
    auto service = DartsScoreJsonService::createInstance()
            ->setAssembleJsonFromDartsMultiAttemptScores(new AssembleJsonFromDartsMultiAttemptScores)
            ->setAssembleJsonByDartsScoreIndexes(new AssembleJsonByDartsScoreIndexes);
    return service;
}
