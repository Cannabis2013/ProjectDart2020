#include "defaultmodelsservicebuilder.h"

DefaultModelsServiceBuilder *DefaultModelsServiceBuilder::createInstance()
{
    return new DefaultModelsServiceBuilder();
}

AbstractModelsService *DefaultModelsServiceBuilder::buildLocalModelsServiceWithJsonDb()
{
    auto dartsModelsService = _localDartsTournamentServiceBuilder->buildModelsService();
    auto playerModelsService = _playerServiceBuilder->buildModelsService();
    auto modelsContext = LocalModelsService::createInstance()
            ->setAssembleJsonDartsIndexes(new AssembleJsonFromDartsPointIndexes)
            ->setGetPlayerIndexesFromJson(new GetPlayerIndexesFromJson)
            ->setAssembleJsonFromPlayerNamesAndIds(new JsonArrayFromPlayerNamesAndIds)
            ->setAssembleJsonFromTournamentDartsPoints(new AssembleJsonFromDartsPoints())
            ->setAssembleJsonFromOrderedDartsPointModels(new AssembleJsonFromOrderedDartsPointModels)
            ->setAssembleDartsTournamentFromJson(new AssembleDartsTournamentModelFromJson)
            ->setAssembleJsonDartsTournamentModels(new AssembleJsonDartsTournamentModels)
            ->setDartsModelsService(dartsModelsService)
            ->setPlayerModelsService(playerModelsService)
            ->setAssembleJsonFromPlayerIdAndName(new AssembleJsonFromPlayerNameAndId)
            ->setAssembleJSonBasicTournamentValues(new AssembleJsonBasicTournamentValues)
            ->setGetTournamentIndexesFromJson(new GetTournamentIndexesFromJson)
            ->setGetDeletePlayerIndexFromJson(new GetDeletePlayerIndexFromJson)
            ->setAssembleDartsPointModelFromJson(new AssembleDartsPointModelFromJson)
            ->setAssemblePlayerModelFromJson(new AssemblePlayerModelFromJson)
            ->setAssignPlayerIdsToDartsTournament(new AssignPlayerIdsToDartsTournamentModel)
            ->setAssembleJsonFromDartsTournamentModel(new AssembleJsonFromDartsTournament);
    return modelsContext;
}

DefaultModelsServiceBuilder *DefaultModelsServiceBuilder::setModelsTournamentServiceBuilder(
        IModelsServiceBuilder<IDartsModelsService> *builder)
{
    _localDartsTournamentServiceBuilder = builder;
    return this;
}

DefaultModelsServiceBuilder *DefaultModelsServiceBuilder::setPlayerServiceBuilder(IModelsServiceBuilder<IPlayerModelsService> *playerServiceBuilder)
{
    _playerServiceBuilder = playerServiceBuilder;
    return this;
}
