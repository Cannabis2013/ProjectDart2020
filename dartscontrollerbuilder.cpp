#include "dartscontrollerbuilder.h"

using namespace DartsBuilderContext;

DartsControllerBuilder* DartsControllerBuilder::createInstance()
{
    return new DartsControllerBuilder();
}

AbstractGameController *DartsControllerBuilder::assembleDartsGameController(const QByteArray &json,
                                                                            AbstractApplicationInterface *applicationInterface,
                                                                            AbstractModelsService *modelsContext)
{
    auto entity = _buildEntityByJson->service(json);
    auto inputHint = entity->inputHint();
    if(inputHint == InputModes::PointMode)
    {
        AbstractDartsPointController* controller = nullptr;
        controller = assembleDartsPointController(entity);
        _connectDartsSingleAttemptPointController->service(controller,applicationInterface,modelsContext);
        emit sendController(controller);
        return controller;
    }
    else if(inputHint == InputModes::ScoreMode)
    {
        AbstractDartsScoreController* controller = nullptr;
        controller = assembleDartsScoreController(entity);
        _connectDartsScoreController->service(controller,applicationInterface,modelsContext);
        emit sendController(controller);
        return controller;
    }
    else
        throw "Invalid inputmode";
}

void DartsControllerBuilder::determineTournamentGameMode(const QUuid &tournament, const int &gameMode)
{
    if(gameMode == GameModes::FirstToPost)
        emit requestDartsDetails(tournament);
}

AbstractDartsPointController *DartsControllerBuilder::assembleDartsPointController(const ControllerEntity *entity)
{
    using namespace DartsPointSingleAttemptContext;
    AbstractDartsPointController* controller = DartsPointSingleAttempt::createInstance(entity->tournamentId())
            ->setLogisticInterface(DartsPointLogisticController::createInstance(entity->attempts(),
                                                                                entity->terminalKeyCode()))
            ->setScoreCalculator(DartsPointCalculator::createInstance())
            ->setInputValidator(PointValidator::createInstance(entity->terminalKeyCode()))
            ->setIndexController(PointIndexController::createInstance(entity->attempts()))
            ->setInputController(DartsPlayerPointService::createInstance(entity->keyPoint(),entity->winnerId()))
            ->setDartsJsonModelsService(new DartsPointJsonService)
            ->setAssembleDartsPointTurnValues(new BuildDartsPointTurnValues)
            ->setDartsPointBuilderService(new DartsControllerPointBuilder)
            ->setBuildDartsIndexesByJson(new DartsIndexesBuilderService)
            ->setControllerModelsService(new DartsControllerPointModelsService)
            ->setPlayerModelBuilderService(new DartsPlayerModelBuilderService);
    return controller;
}

AbstractDartsScoreController *DartsControllerBuilder::assembleDartsScoreController(const ControllerEntity *entity)
{
    using namespace DartsScoreMultiAttemptContext;
    AbstractDartsScoreController* controller =
            DartsScoreMultiAttemptContext::DartsScoreMultiAttempt::createInstance(entity->tournamentId())
            ->setLogisticInterface(DartsScoreLogisticController::createInstance(entity->attempts(),
                                                                                entity->terminalKeyCode()))
            ->setInputValidator(ScoreValidator::createInstance(entity->terminalKeyCode()))
            ->setIndexController(ScoreIndexController::createInstance())
            ->setScoreController(DartsPlayerScoreService::createInstance(entity->keyPoint(),
                                                                         entity->winnerId()))
            ->setJsonService(new DartsScoreJsonBuilderService)
            ->setDetermineControllerStateByWinnerId(new DetermineControllerStateByWinnerId)
            ->setAddAccumulatedScoreToModel(new AddAccumulatedScoreToDartsScore)
            ->setTurnValuesBuilderService(new AssembleDartsScoreTurnValues)
            ->setDartsScoreBuilderService(new DartsScoreModelsBuilderService)
            ->setDartsIndexesBuilderService(new DartsScoreIndexesBuilderService)
            ->setDartsJsonExtractorService(new DartsScoreJsonExtractor)
            ->setPlayerBuilderService(new DartsPlayerBuilderService);
    return controller;
}

DartsControllerBuilder* DartsControllerBuilder::setConnectDartsMultiAttemptScoreController(ITernaryService<AbstractDartsScoreController *, AbstractApplicationInterface *, AbstractModelsService *, void> *connectDartsScoreController)
{
    _connectDartsScoreController = connectDartsScoreController;
    return this;
}

DartsControllerBuilder* DartsControllerBuilder::setConnectDartsSingleAttemptPointController(ITernaryService<AbstractDartsPointController *, AbstractApplicationInterface *, AbstractModelsService *, AbstractDartsPointController *> *connectDartsPointController)
{
    _connectDartsSingleAttemptPointController = connectDartsPointController;
    return this;
}
