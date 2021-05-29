#include "defaultmodelsservicebuilder.h"

DefaultModelsServiceBuilder *DefaultModelsServiceBuilder::createInstance()
{
    return new DefaultModelsServiceBuilder();
}

AbstractModelsService *DefaultModelsServiceBuilder::buildLocalModelsServiceWithJsonDb()
{
    auto dartsJsonModelsService = _dartsJSonServiceBuilder->buildModelsService();
    auto dartsModelsService = _localDartsTournamentServiceBuilder->buildModelsService();
    auto playerModelsService = _playerServiceBuilder->buildModelsService();
    auto modelsContext = LocalModelsService::createInstance()
            ->setDartsModelsService(dartsModelsService)
            ->setPlayerModelsService(playerModelsService)
            ->setDartsJsonService(dartsJsonModelsService)
            ->setAddPlayerNameToDartsInputModel(new AddPlayerNameToDartsInputModel)
            ->setDartsTournamentBuilder(new DartsTournamentBuilder);
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
