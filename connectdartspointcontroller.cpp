#include "connectdartspointcontroller.h"

AbstractDartsPointController *ConnectDartsPointController::service(AbstractDartsPointController *controller,
                                                                   AbstractApplicationInterface *application,
                                                                   AbstractModelsService *modelsService)
{
    // Send tournament metadata
    QObject::connect(application,&AbstractApplicationInterface::requestCurrentTournamentId,
            controller,&AbstractDartsPointController::handleRequestForCurrentTournamentMetaData);
    QObject::connect(controller,&AbstractDartsPointController::sendCurrentTournamentId,
            modelsService,&AbstractModelsService::assembleDartsTournamentDataFromId);
    // Controller requests indexes and playerscores
    QObject::connect(controller,&AbstractDartsPointController::requestDartsIndexesAndPoints,
            modelsService,&AbstractModelsService::assembleDartsIndexesAndPoints);
    QObject::connect(modelsService,&AbstractModelsService::sendDartsIndexesAndPointValues,
            controller,&AbstractDartsController::initializeController);
    // Controller requests transmitting multithrow playerscores
    QObject::connect(application,&AbstractApplicationInterface::requestDartsMultiAttemptScores,
            controller,&AbstractDartsPointController::handleRequestDartsPoints);
    QObject::connect(controller,&AbstractDartsPointController::requestDartsPoints,
            modelsService,&AbstractModelsService::getOrderedDartsPoints);
    QObject::connect(modelsService,&AbstractModelsService::sendFtpMultiScores,
            controller,&AbstractDartsPointController::sendMultiAttemptDartsPoints);
    QObject::connect(controller,&AbstractDartsPointController::sendMultiAttemptDartsPoints,
            application,&AbstractApplicationInterface::sendAssembledMultiFtpScores);
    /*
         * Controller requests transmitting singlethrow playerscores
         */
    QObject::connect(application,&AbstractApplicationInterface::requestSingleThrowPlayerScores,
            controller,&AbstractDartsPointController::assembleSingleAttemptDartsPoints);
    QObject::connect(controller,&AbstractDartsPointController::sendSingleAttemptDartsPoints,
            application,&AbstractApplicationInterface::sendAssembledSingleFtpScores);
    /*
         * Wake up controller
         */
    QObject::connect(application,&AbstractApplicationInterface::requestWakeUp,
            controller,&AbstractGameController::beginInitialize);
    /*
         * Controller needs to inform external context about its state
         */
    QObject::connect(controller,&AbstractDartsController::controllerIsStopped,
            application,&AbstractApplicationInterface::controllerIsStopped);
    QObject::connect(controller,&AbstractDartsController::controllerIsInitialized,
            application,&AbstractApplicationInterface::controllerIsInitialized);
    QObject::connect(controller,&AbstractDartsController::isReadyAndAwaitsInput,
            application,&AbstractApplicationInterface::controllerAwaitsInput);
    QObject::connect(controller,&AbstractDartsController::winnerDeclared,
            application,&AbstractApplicationInterface::controllerHasDeclaredAWinner);
    /*
         * Start/stop game
         */
    QObject::connect(application,&AbstractApplicationInterface::requestStartGame,
            controller,&AbstractGameController::start);
    QObject::connect(application,&AbstractApplicationInterface::requestStopGame,
            controller,&AbstractGameController::stop);
    /*
         * Reset tournament
         */
    QObject::connect(application,&AbstractApplicationInterface::requestTournamentReset,
            controller,&AbstractGameController::handleResetTournament);
    QObject::connect(controller,&AbstractGameController::requestResetTournament,
            modelsService,&AbstractModelsService::resetTournament);
    QObject::connect(modelsService,&AbstractModelsService::tournamentResetSuccess,
            controller,&AbstractGameController::isReset);
    QObject::connect(controller,&AbstractDartsController::isReset,
            application,&AbstractApplicationInterface::ftpControllerIsReset);
    /*
         * Add point
         */
    QObject::connect(application,&AbstractApplicationInterface::sendPoint,
            controller,&AbstractGameController::handleAndProcessUserInput);
    QObject::connect(controller,&AbstractDartsPointController::requestAddDartsPoint,
            modelsService,&AbstractModelsService::addDartsPoint);
    QObject::connect(modelsService,&AbstractModelsService::scoreAddedToDataContext,
            controller,&AbstractGameController::handleScoreAddedToDataContext);
    QObject::connect(controller,&AbstractDartsPointController::pointAddedAndPersisted,
            application,&AbstractApplicationInterface::ftpControllerAddedAndPersistedScore);
    QObject::connect(application,&AbstractApplicationInterface::requestControllerState,
            controller,&AbstractGameController::handleRequestFromUI);
    /*
         * Controller remove has removed scores
         */
    QObject::connect(controller,&AbstractDartsPointController::pointRemoved,
            application,&AbstractApplicationInterface::ftpControllerRemovedScore);
    /*
         * Undo/redo
         */
    QObject::connect(application,&AbstractApplicationInterface::requestUndo,
            controller,&AbstractDartsPointController::undoTurn);
    QObject::connect(controller,&AbstractDartsPointController::hideDartsPoint,
            modelsService,&AbstractModelsService::hideDartsPoint);
    QObject::connect(modelsService,&AbstractModelsService::hideDartsPointSuccess,
            controller,&AbstractDartsPointController::undoSuccess);
    QObject::connect(application,&AbstractApplicationInterface::requestRedo,
            controller,&AbstractDartsPointController::redoTurn);
    QObject::connect(controller,&AbstractDartsPointController::hideDartsPoint,
            modelsService,&AbstractModelsService::revealPoint);
    QObject::connect(modelsService,&AbstractModelsService::revealDartsPointSuccess,
            controller,&AbstractDartsPointController::redoSuccess);
    return controller;
}

