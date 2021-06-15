#include "defaultmodelsservicebuilder.h"

using namespace DartsModelsContext;

DefaultModelsServiceBuilder *DefaultModelsServiceBuilder::createInstance()
{
    return new DefaultModelsServiceBuilder();
}

AbstractModelsService *DefaultModelsServiceBuilder::buildLocalModelsServiceWithJsonDb()
{
    auto dartsPointDb = DartsPointJsonDbService::createInstance(new AssembleDartsPointsFromJson,
                                                            new AssembleJsonArrayFromDartsPoints);
    auto dartsScoreDb = DartsScoreJsonDb::createInstance(new AssembleMultiAttemptScoresByJson,
                                                         new AssembleJsonByDartsScoreModels);
    auto modelsContext = LocalModelsService::createInstance()
            ->setDartsModelsService(_localDartsTournamentServiceBuilder->buildModelsService())
            ->setPlayerModelsService(_playerServiceBuilder->buildModelsService())
            ->setDartsJsonService(_dartsJsonServiceBuilder->buildDartsJsonService())
            ->setDartsScoreInputModelsService(_dartsScoreModelsServiceBuilder->buildModelsService())
            ->setDartsPointInputService(_dartsPointModelsServiceBuilder->buildModelsService())
            ->setAddPlayerNameToDartsInputModel(new AddPlayerNameToDartsInputModel)
            ->setDartsTournamentBuilder(new DartsTournamentBuilder)
            ->setDartsPointInputDb(dartsPointDb)
            ->setDartsScoreInputDb(dartsScoreDb)
            ->setGetInputModelsService(new GetInputModelsService)
            ->setDbManipulatorService(new DefaultDbManipulatorService)
            ->setInputModelsSortService(new InputModelsSortService)
            ->setSortPointInputsByIndexes(new SortDartsPointInputsByIndexes)
            ->setInputModelsScountervice(new InputModelsCountService)
            ->setDartsPointsJsonService(_dartsJsonServiceBuilder->buildDartsPointsJsonService())
            ->setDartsScoresJsonService(_dartsJsonServiceBuilder->buildDartsScoreJsonService())
            ->setPlayerModelsJsonService(_playerJsonServiceBuilder->buildModelsService());
    return modelsContext;
}
