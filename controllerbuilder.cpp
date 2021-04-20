#include "controllerbuilder.h"

AbstractGameController *ControllerBuilder::assembleFTPGameController(const QByteArray &json,
                                                                     AbstractApplicationInterface *applicationInterface,
                                                                     AbstractModelsContext *modelsContext)
{
    auto jsonObject = QJsonDocument::fromJson(json).object();
    auto tournamentId = jsonObject.value("tournamentId").toString();
    auto keyPoint = jsonObject.value("keyPoint").toInt();
    auto attempts = jsonObject.value("attempts").toInt();
    auto terminalKeyCode = jsonObject.value("terminalKeyCode").toInt();
    auto inputHint = jsonObject.value("inputHint");
    auto winnerStringId = jsonObject.value("winnerId").toString();
    auto winnerId = QUuid::fromString(winnerStringId);
    AbstractFtpController* controller = nullptr;
    if(inputHint == InputModes::PointMode)
    {
        controller = assembleFtpPointBasedController(tournamentId,winnerId,keyPoint,
                                                     terminalKeyCode,attempts);
    }
    else if(inputHint == InputModes::ScoreMode)
    {
        controller = assembleFtpScoreBasedController(tournamentId,winnerId,
                                                     keyPoint,terminalKeyCode,
                                                     attempts);
    }
    else
        throw "Invalid inputmode";
    connectFTPController(controller,applicationInterface,modelsContext);
    emit sendController(controller);
    return controller;
}

void ControllerBuilder::determineTournamentGameMode(const QUuid &tournament, const int &gameMode)
{
    if(gameMode == GameModes::FirstToPost)
        emit requestFTPDetails(tournament);
}

AbstractFtpController *ControllerBuilder::assembleFtpPointBasedController(const QUuid &tournament,
                                                                          const QUuid &winnerId,
                                                                          const int &keyPoint,
                                                                          const int &terminalKeyCode,
                                                                          const int &attempts)
{
    AbstractFtpController* controller = LocalFtpController::createInstance(tournament)
            ->setLogisticInterface(PointLogisticController::createInstance(attempts,
                                                                           terminalKeyCode))
            ->setScoreCalculator(PointScoreCalculator::createInstance())
            ->setInputValidator(PointValidator::createInstance(terminalKeyCode))
            ->setIndexController(PointIndexController::createInstance(attempts))
            ->setScoreController(FTPScoreController::createInstance(keyPoint,
                                                                    winnerId));
    return controller;
}

AbstractFtpController *ControllerBuilder::assembleFtpScoreBasedController(const QUuid &tournament,
                                                                          const QUuid &winnerId,
                                                                          const int &keyPoint,
                                                                          const int &terminalKeyCode,
                                                                          const int &attempts)
{
    AbstractFtpController* controller = LocalFtpController::createInstance(tournament)
            ->setLogisticInterface(ScoreLogisticController::createInstance(attempts,terminalKeyCode))
            ->setScoreCalculator(new ScoreCalculator())
            ->setInputValidator(ScoreValidator::createInstance(terminalKeyCode))
            ->setIndexController(ScoreIndexController::createInstance())
            ->setScoreController(FTPScoreController::createInstance(keyPoint,
                                                                    winnerId));
    return controller;
}

void ControllerBuilder::connectFTPController(AbstractFtpController *controller, AbstractApplicationInterface *applicationInterface, AbstractModelsContext *modelsContext)
{
    /*
         * Send tournament metadata
         */
    connect(applicationInterface,&AbstractApplicationInterface::requestCurrentTournamentId,
            controller,&AbstractFtpController::handleRequestForCurrentTournamentMetaData);
    connect(controller,&AbstractFtpController::sendCurrentTournamentId,
            modelsContext,&AbstractModelsContext::assembleFtpMetaDataFromId);
    /*
         * Controller requests indexes and playerscores
         */
    connect(controller,&AbstractFtpController::requestFtpIndexesAndScores,
            modelsContext,&AbstractModelsContext::assembleFtpIndexesAndScores);
    connect(modelsContext,&AbstractModelsContext::sendFtpIndexesAndScoreEntities,
            controller,&AbstractFtpController::initializeController);
    /*
         * Controller requests transmitting multithrow playerscores
         */
    connect(applicationInterface,&AbstractApplicationInterface::requestFtpMultiAttemptScores,
            controller,&AbstractFtpController::handleRequestFtpPlayerScores);
    connect(controller,&AbstractFtpController::requestFtpMultiAttemptScores,
            modelsContext,&AbstractModelsContext::handleRequestFtpScores);
    connect(modelsContext,&AbstractModelsContext::sendFtpMultiScores,
            controller,&AbstractFtpController::sendMultiAttemptFtpScores);
    connect(controller,&AbstractFtpController::sendMultiAttemptFtpScores,
            applicationInterface,&AbstractApplicationInterface::sendAssembledMultiFtpScores);
    /*
         * Controller requests transmitting singlethrow playerscores
         */
    connect(applicationInterface,&AbstractApplicationInterface::requestSingleThrowPlayerScores,
            controller,&AbstractFtpController::assembleSingleAttemptFtpScores);
    connect(controller,&AbstractFtpController::sendSingleAttemptFtpScores,
            applicationInterface,&AbstractApplicationInterface::sendAssembledSingleFtpScores);
    /*
         * Wake up controller
         */
    connect(applicationInterface,&AbstractApplicationInterface::requestWakeUp,
            controller,&AbstractGameController::beginInitialize);
    /*
         * Controller needs to inform external context about its state
         */
    connect(controller,&AbstractFtpController::controllerIsStopped,
            applicationInterface,&AbstractApplicationInterface::controllerIsStopped);
    connect(controller,&AbstractFtpController::controllerIsInitialized,
            applicationInterface,&AbstractApplicationInterface::controllerIsInitialized);
    connect(controller,&AbstractFtpController::isReadyAndAwaitsInput,
            applicationInterface,&AbstractApplicationInterface::controllerAwaitsInput);
    connect(controller,&AbstractFtpController::winnerDeclared,
            applicationInterface,&AbstractApplicationInterface::controllerHasDeclaredAWinner);
    /*
         * Start/stop game
         */
    connect(applicationInterface,&AbstractApplicationInterface::requestStartGame,
            controller,&AbstractGameController::start);
    connect(applicationInterface,&AbstractApplicationInterface::requestStopGame,
            controller,&AbstractGameController::stop);
    /*
         * Reset tournament
         */
    connect(applicationInterface,&AbstractApplicationInterface::requestTournamentReset,
            controller,&AbstractGameController::handleResetTournament);
    connect(controller,&AbstractGameController::requestResetTournament,
            modelsContext,&AbstractModelsContext::resetTournament);
    connect(modelsContext,&AbstractModelsContext::tournamentResetSuccess,
            controller,&AbstractGameController::isReset);
    connect(controller,&AbstractFtpController::isReset,
            applicationInterface,&AbstractApplicationInterface::ftpControllerIsReset);
    /*
         * Add point
         */
    connect(applicationInterface,&AbstractApplicationInterface::sendPoint,
            controller,&AbstractGameController::handleAndProcessUserInput);
    connect(controller,&AbstractFtpController::requestAddFtpScore,
            modelsContext,&AbstractModelsContext::addFtpScore);
    connect(modelsContext,&AbstractModelsContext::scoreAddedToDataContext,
            controller,&AbstractGameController::handleScoreAddedToDataContext);
    connect(controller,&AbstractFtpController::scoreAddedAndPersisted,
            applicationInterface,&AbstractApplicationInterface::ftpControllerAddedAndPersistedScore);
    connect(applicationInterface,&AbstractApplicationInterface::requestControllerState,
            controller,&AbstractGameController::handleRequestFromUI);
    /*
         * Controller remove has removed scores
         */
    connect(controller,&AbstractFtpController::scoreRemoved,
            applicationInterface,&AbstractApplicationInterface::ftpControllerRemovedScore);
    /*
         * Undo/redo
         */
    connect(applicationInterface,&AbstractApplicationInterface::requestUndo,
            controller,&AbstractGameController::undoTurn);
    connect(applicationInterface,&AbstractApplicationInterface::requestRedo,
            controller,&AbstractGameController::redoTurn);
    connect(controller,&AbstractGameController::requestSetModelHint,
            modelsContext,&AbstractModelsContext::setFtpScoreHint);
    connect(modelsContext,&AbstractModelsContext::scoreHintUpdated,
            controller,&AbstractGameController::handleScoreHintUpdated);
}
