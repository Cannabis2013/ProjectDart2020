#include "defaultmodelsservicebuilder.h"

DefaultModelsServiceBuilder *DefaultModelsServiceBuilder::createInstance()
{
    return new DefaultModelsServiceBuilder();
}

AbstractModelsService *DefaultModelsServiceBuilder::buildLocalModelsServiceWithJsonDb()
{
    auto dartsPointDb = DartsPointJsonDbService::createInstance(new AssembleSingleAttemptPointsFromJson,
                                                            new AssembleJsonArrayFromDartsPoints);
    auto dartsScoreDb = DartsScoreJsonDb::createInstance(new AssembleMultiAttemptScoresByJson,
                                                         new AssembleJsonByDartsScoreModels);
    auto modelsContext = LocalModelsService::createInstance()
            ->setDartsModelsService(_localDartsTournamentServiceBuilder->buildModelsService())
            ->setPlayerModelsService(_playerServiceBuilder->buildModelsService())
            ->setDartsJsonService(_dartsJSonServiceBuilder->buildModelsService())
            ->setDartsScoreInputModelsService(_dartsScoreModelsServiceBuilder->buildModelsService())
            ->setDartsPointInputService(_dartsPointModelsServiceBuilder->buildModelsService())
            ->setAddPlayerNameToDartsInputModel(new AddPlayerNameToDartsInputModel)
            ->setDartsTournamentBuilder(new DartsTournamentBuilder)
            ->setDartsPointInputDb(dartsPointDb)
            ->setDartsScoreInputDb(dartsScoreDb)
            ->setGetInputModelsService(new GetInputModelsService)
            ->setDbManipulatorService(new DefaultDbManipulatorService)
            ->setInputModelsSortService(new InputModelsSortService)
            ->setSortPointInputsByIndexes(new SortDartsPointInputsByIndexes);
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

DefaultModelsServiceBuilder *DefaultModelsServiceBuilder::setDartsJSonServiceBuilder(IModelsServiceBuilder<IDartsJsonService> *dartsJSonServiceBuilder)
{
    _dartsJSonServiceBuilder = dartsJSonServiceBuilder;
    return this;
}

DefaultModelsServiceBuilder *DefaultModelsServiceBuilder::setDartsScoreModelsServiceBuilder(IModelsServiceBuilder<ScoreModelsService> *newDartsScoreModelsServiceBuilder)
{
    _dartsScoreModelsServiceBuilder = newDartsScoreModelsServiceBuilder;
    return this;
}

DefaultModelsServiceBuilder *DefaultModelsServiceBuilder::setDartsPointModelsServiceBuilder(IModelsServiceBuilder<IDartsPointModelsService<IDartsPointDb>> *newDartsPointModelsServiceBuilder)
{
    _dartsPointModelsServiceBuilder = newDartsPointModelsServiceBuilder;
    return this;
}
