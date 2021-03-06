#include "dartscontrollerbuilder.h"

DartsControllerBuilder* DartsControllerBuilder::createInstance()
{
    return new DartsControllerBuilder();
}

AbstractGameController *DartsControllerBuilder::assembleDartsGameController(const QByteArray &json,
                                                                     AbstractApplicationInterface *applicationInterface,
                                                                     AbstractModelsService *modelsContext)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    auto tournamentStringId = jsonObject.value("tournamentId").toString();
    auto tournamentId = QUuid::fromString(tournamentStringId);
    auto keyPoint = jsonObject.value("keyPoint").toInt();
    auto attempts = jsonObject.value("attempts").toInt();
    auto terminalKeyCode = jsonObject.value("terminalKeyCode").toInt();
    auto inputHint = jsonObject.value("inputHint");
    auto winnerStringId = jsonObject.value("winnerId").toString();
    auto winnerId = QUuid::fromString(winnerStringId);
    if(inputHint == InputModes::PointMode)
    {
        AbstractDartsPointController* controller = nullptr;
        controller = assembleDartsPointController(tournamentId,
                                                     winnerId,
                                                     keyPoint,
                                                     terminalKeyCode,
                                                     attempts);
        _connectDartsSingleAttemptPointController->service(controller,applicationInterface,modelsContext);
        emit sendController(controller);
        return controller;
    }
    else if(inputHint == InputModes::ScoreMode)
    {
        AbstractDartsScoreController* controller = nullptr;
        controller = assembleDartsScoreController(tournamentId,winnerId,
                                                     keyPoint,terminalKeyCode,
                                                     attempts);
        _connectDartsScoreController->service(controller,applicationInterface,modelsContext);
        emit sendController(controller);
        return controller;
    }
    else
        throw "Invalid inputmode";
    //connectDartsPointController(controller,applicationInterface,modelsContext);
}

void DartsControllerBuilder::determineTournamentGameMode(const QUuid &tournament, const int &gameMode)
{
    if(gameMode == GameModes::FirstToPost)
        emit requestDartsDetails(tournament);
}

AbstractDartsPointController *DartsControllerBuilder::assembleDartsPointController(const QUuid &tournament,
                                                                                 const QUuid &winnerId,
                                                                                 const int &keyPoint,
                                                                                 const int &terminalKeyCode,
                                                                                 const int &attempts)
{
    using namespace DartsPointSingleAttemptContext;
    AbstractDartsPointController* controller = DartsPointSingleAttempt::createInstance(tournament)
            ->setLogisticInterface(DartsPointLogisticController::createInstance(attempts,
                                                                           terminalKeyCode))
            ->setScoreCalculator(DartsPointCalculator::createInstance())
            ->setInputValidator(PointValidator::createInstance(terminalKeyCode))
            ->setIndexController(PointIndexController::createInstance(attempts))
            ->setInputController(DartsPlayerPointService::createInstance(keyPoint,winnerId))
            ->setDartsJsonModelsService(new DartsPointJsonService)
            ->setAssembleDartsPointTurnValues(new BuildDartsPointTurnValues)
            ->setDartsPointBuilderService(new DartsControllerPointBuilder)
            ->setBuildDartsIndexesByJson(new DartsIndexesBuilderService)
            ->setControllerModelsService(new DartsControllerPointModelsService);
    return controller;
}

AbstractDartsScoreController *DartsControllerBuilder::assembleDartsScoreController(const QUuid &tournament,
                                                                                 const QUuid &winnerId,
                                                                                 const int &keyPoint,
                                                                                 const int &terminalKeyCode,
                                                                                 const int &attempts)
{
    using namespace DartsScoreMultiAttemptContext;
    AbstractDartsScoreController* controller =
            DartsScoreMultiAttemptContext::DartsScoreMultiAttempt::createInstance(tournament)
            ->setLogisticInterface(DartsScoreLogisticController::createInstance(attempts,terminalKeyCode))
            ->setInputValidator(ScoreValidator::createInstance(terminalKeyCode))
            ->setIndexController(ScoreIndexController::createInstance())
            ->setScoreController(DartsPlayerScoreService::createInstance(keyPoint,winnerId))
            ->setJsonService(new DartsMultiAttemptJsonService)
            ->setAssembleDartsScoreByJsonService(new AssembleDartsScoreByJson)
            ->setAssembleDartsScoresByJsonService(new AssembleDartsScoresByJson)
            ->setAssembleDartsPlayersByJson(new AssembleDartsPlayersByJson)
            ->setAssembleDartsPlayerByJson(new AssembleDartsPlayerByJson)
            ->setDetermineControllerStateByWinnerId(new DetermineControllerStateByWinnerId)
            ->setAssembleDartsScoreIndexesByJson(new AssembleDartsScoreIndexesByJson)
            ->setAddAccumulatedScoreToModel(new AddAccumulatedScoreToDartsScore)
            ->setAssembleDartsScoreTurnValues(new AssembleDartsScoreTurnValues);
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
