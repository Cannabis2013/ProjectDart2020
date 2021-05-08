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
    auto tournamentId = jsonObject.value("tournamentId").toString();
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
    AbstractDartsPointController* controller = DartsPointController::createInstance(tournament)
            ->setLogisticInterface(PointLogisticController::createInstance(attempts,
                                                                           terminalKeyCode))
            ->setScoreCalculator(PointScoreCalculator::createInstance())
            ->setInputValidator(PointValidator::createInstance(terminalKeyCode))
            ->setIndexController(PointIndexController::createInstance(attempts))
            ->setScoreController(DartsScoreController::createInstance(keyPoint,
                                                                    winnerId));
    return controller;
}

AbstractDartsScoreController *DartsControllerBuilder::assembleDartsScoreController(const QUuid &tournament,
                                                                                 const QUuid &winnerId,
                                                                                 const int &keyPoint,
                                                                                 const int &terminalKeyCode,
                                                                                 const int &attempts)
{
    AbstractDartsScoreController* controller = ScoreDartsController::createInstance(tournament)
            ->setLogisticInterface(ScoreLogisticController::createInstance(attempts,terminalKeyCode))
            ->setScoreCalculator(new ScoreCalculator())
            ->setInputValidator(ScoreValidator::createInstance(terminalKeyCode))
            ->setIndexController(ScoreIndexController::createInstance())
            ->setScoreController(DartsScoreController::createInstance(keyPoint,
                                                                    winnerId));
    return controller;
}

DartsControllerBuilder* DartsControllerBuilder::setConnectDartsScoreController(ITernaryService<AbstractDartsScoreController *, AbstractApplicationInterface *, AbstractModelsService *, AbstractDartsScoreController *> *connectDartsScoreController)
{
    _connectDartsScoreController = connectDartsScoreController;
}

DartsControllerBuilder* DartsControllerBuilder::setConnectDartsSingleAttemptPointController(ITernaryService<AbstractDartsPointController *, AbstractApplicationInterface *, AbstractModelsService *, AbstractDartsPointController *> *connectDartsPointController)
{
    _connectDartsSingleAttemptPointController = connectDartsPointController;
    return this;
}
