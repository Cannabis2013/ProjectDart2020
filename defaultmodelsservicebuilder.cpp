#include "defaultmodelsservicebuilder.h"

DefaultModelsServiceBuilder *DefaultModelsServiceBuilder::createInstance()
{
    return new DefaultModelsServiceBuilder();
}

AbstractModelsService *DefaultModelsServiceBuilder::buildLocalModelsServiceWithJsonDb(AbstractApplicationInterface *applicationInterface)
{
    auto modelsContext = LocalModelsService::createInstance();
    modelsContext->setAssembleJsonDartsIndexes(new AssembleJsonFromDartsPointIndexes);
    modelsContext->setGetPlayerIndexesFromJson(new AssemblePlayerIndexesFromJson);
    modelsContext->setAssembleJsonFromPlayerNamesAndIds(new JsonArrayFromPlayerNamesAndIds);
    modelsContext->setAssembleJSonFromTournamentDartsPoints(new AssembleJsonFromDartsPoints());
    modelsContext->setAssembleJsonFromOrderedDartsPointModels(new AssembleJsonFromOrderedDartsPointModels);
    modelsContext->setAssembleDartsTournamentFromJson(new AssembleDartsTournamentModelFromJson);
    modelsContext->setAssembleJsonDartsTournamentModels(new AssembleJsonDartsTournamentModels);
    modelsContext->setDartsModelsService(_tournamentServiceBuilder->buildModelsService());
    modelsContext->setPlayerModelsService(_playerServiceBuilder->buildModelsService());
    modelsContext->setAssembleJsonFromPlayerIdAndName(new AssembleJsonFromPlayerNameAndId);
    return modelsContext;
}

DefaultModelsServiceBuilder *DefaultModelsServiceBuilder::setModelsTournamentServiceBuilder(
        IModelsServiceBuilder<IDartsModelsService> *builder)
{
    _tournamentServiceBuilder = builder;
    return this;
}

DefaultModelsServiceBuilder *DefaultModelsServiceBuilder::setPlayerServiceBuilder(IModelsServiceBuilder<IPlayerModelsService<IPlayerModel<QUuid, QString> > > *playerServiceBuilder)
{
    _playerServiceBuilder = playerServiceBuilder;
    return this;
}
