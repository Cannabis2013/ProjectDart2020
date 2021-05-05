#include "connectdartsscorecontroller.h"


AbstractDartsScoreController *ConnectDartsScoreController::service(AbstractDartsScoreController* controller,
                                                                   AbstractApplicationInterface* application,
                                                                   AbstractModelsService* modelsService)
{
    // Send tournament metadata
    QObject::connect(application,&AbstractApplicationInterface::requestCurrentTournamentId,
            controller,&AbstractDartsScoreController::handleRequestForCurrentTournamentMetaData);
    QObject::connect(controller,&AbstractDartsScoreController::sendCurrentTournamentId,
            modelsService,&AbstractModelsService::assembleDartsTournamentDataFromId);
    // Controller requests indexes and playerscores
    QObject::connect(controller,&AbstractDartsScoreController::requestDartsIndexesAndScores,
            modelsService,&AbstractModelsService::assembleDartsIndexesAndScores);
    QObject::connect(modelsService,&AbstractModelsService::sendDartsIndexesAndScoreValues,
            controller,&AbstractDartsScoreController::initializeController);
    // Controller requests transmitting multithrow playerscores
    QObject::connect(application,&AbstractApplicationInterface::requestDartsMultiAttemptScores,
            controller,&AbstractDartsScoreController::handleRequestDartsScores);
    QObject::connect(controller,&AbstractDartsScoreController::requestDartsScores,
            modelsService,&AbstractModelsService::getOrderedDartsPoints);
    QObject::connect(modelsService,&AbstractModelsService::sendFtpMultiScores,
            controller,&AbstractDartsScoreController::sendMultiAttemptDartsScores);
    QObject::connect(controller,&AbstractDartsScoreController::sendMultiAttemptDartsScores,
            application,&AbstractApplicationInterface::sendAssembledMultiFtpScores);
    /*
         * Controller requests transmitting singlethrow playerscores
         */
    QObject::connect(application,&AbstractApplicationInterface::requestSingleThrowPlayerScores,
            controller,&AbstractDartsScoreController::assembleSingleAttemptDartsScores);
    QObject::connect(controller,&AbstractDartsScoreController::sendSingleAttemptDartsScores,
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
    QObject::connect(controller,&AbstractDartsScoreController::requestAddDartsScore,
            modelsService,&AbstractModelsService::addDartsPoint);
    QObject::connect(modelsService,&AbstractModelsService::scoreAddedToDataContext,
            controller,&AbstractGameController::handleScoreAddedToDataContext);
    QObject::connect(controller,&AbstractDartsScoreController::scoreAddedSuccess,
            application,&AbstractApplicationInterface::ftpControllerAddedAndPersistedScore);
    QObject::connect(application,&AbstractApplicationInterface::requestControllerState,
            controller,&AbstractGameController::handleRequestFromUI);
    /*
         * Controller remove has removed scores
         */
    QObject::connect(controller,&AbstractDartsScoreController::scoreRemoved,
            application,&AbstractApplicationInterface::ftpControllerRemovedScore);
    /*
         * Undo/redo
         */
    QObject::connect(application,&AbstractApplicationInterface::requestUndo,
            controller,&AbstractDartsScoreController::undoTurn);
    QObject::connect(controller,&AbstractDartsScoreController::hideDartsScore,
            modelsService,&AbstractModelsService::hideDartsScore);
    QObject::connect(modelsService,&AbstractModelsService::hideDartsScoreSuccess,
            controller,&AbstractDartsScoreController::undoSuccess);
    QObject::connect(application,&AbstractApplicationInterface::requestRedo,
            controller,&AbstractDartsScoreController::redoTurn);
    QObject::connect(controller,&AbstractDartsScoreController::hideDartsScore,
            modelsService,&AbstractModelsService::revealScore);
    QObject::connect(modelsService,&AbstractModelsService::revealDartsScoreSuccess,
            controller,&AbstractDartsScoreController::redoSuccess);
    return controller;
}
