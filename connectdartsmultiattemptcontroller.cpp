#include "connectdartsmultiattemptcontroller.h"

void ConnectDartsMultiAttemptController::service(AbstractDartsScoreController *controller, AbstractApplicationInterface *application, AbstractModelsService *modelsService)
{
    // Send tournament metadata
    QObject::connect(application,&AbstractApplicationInterface::requestCurrentTournamentId,
            controller,&AbstractDartsScoreController::handleRequestForCurrentTournamentMetaData);
    QObject::connect(controller,&AbstractDartsScoreController::sendCurrentTournamentId,
            modelsService,&AbstractModelsService::assembleDartsTournamentDataFromId);
    // Controller requests indexes and playerscores
    QObject::connect(controller,&AbstractDartsScoreController::requestDartsTournamentIndexes,
            modelsService,&AbstractModelsService::assembleDartsScoreIndexes);
    QObject::connect(modelsService,&AbstractModelsService::sendDartsScoreIndexesAsJson,
            controller,&AbstractDartsController::initializeControllerIndexes);
    QObject::connect(controller,&AbstractDartsScoreController::requestTournamentAssignedPlayerDetails,
                     modelsService,&AbstractModelsService::assembleAssignedPlayerEntities);
    QObject::connect(modelsService,&AbstractModelsService::sendAssignedPlayerIdsAndNamesAsJson,
                     controller,&AbstractDartsScoreController::initializeControllerPlayerDetails);
    QObject::connect(controller,&AbstractDartsScoreController::requestTournamentDartsScores,
                     modelsService,&AbstractModelsService::assembleAssignedPlayerScores);
    QObject::connect(modelsService,&AbstractModelsService::sendTournamentDartsScoresAsJson,
                     controller,&AbstractDartsScoreController::initializeControllerDartsScores);
    QObject::connect(controller,&AbstractDartsScoreController::requestTournamentWinnerIdAndName,
                     modelsService,&AbstractModelsService::assembleDartsTournamentWinnerIdAndName);
    QObject::connect(modelsService,&AbstractModelsService::sendDartsTournamentWinnerIdAndName,
                     controller,&AbstractDartsScoreController::initializeControllerWinnerIdAndName);
    QObject::connect(controller,&AbstractDartsScoreController::controllerIsInitialized,
                     application,&AbstractApplicationInterface::dartsMultiAttemptScoreControllerIsInitalized);
    /*
     * UI requests multi attempt playerscores
     */
    QObject::connect(application,&AbstractApplicationInterface::requestDartsMultiAttemptScores,
            controller,&AbstractDartsScoreController::assembleMultiAttemptDartsScores);
    QObject::connect(controller,&AbstractDartsScoreController::sendMultiAttemptDartsScores,
            application,&AbstractApplicationInterface::sendAssembledMultiAttemptDartsScores);
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
    QObject::connect(controller,&AbstractDartsScoreController::controllerIsInitializedAndReady,
            application,&AbstractApplicationInterface::dartsMultiAttemptScoreControllerIsReady);
    QObject::connect(controller,&AbstractDartsController::isReadyAndAwaitsInput,
            application,&AbstractApplicationInterface::controllerAwaitsInput);
    QObject::connect(controller,&AbstractDartsController::winnerDeclared,
            modelsService,&AbstractModelsService::setDartsTournamentWinner);
    QObject::connect(modelsService,&AbstractModelsService::setDartsTournamentWinnerSucces,
                     controller,&AbstractDartsScoreController::winnerDetermined);
    QObject::connect(controller,&AbstractDartsScoreController::winnerDetermined,
                     application,&AbstractApplicationInterface::controllerHasDeclaredAWinner);
    /*
         * Start/stop game
         */
    QObject::connect(application,&AbstractApplicationInterface::requestStartGame,
            controller,&AbstractGameController::start);
    QObject::connect(controller,&AbstractDartsScoreController::isReadyAndAwaitsInput,
                     application,&AbstractApplicationInterface::controllerAwaitsInput);
    QObject::connect(application,&AbstractApplicationInterface::requestStopGame,
            controller,&AbstractGameController::stop);
    /*
         * Reset tournament
         */
    QObject::connect(application,&AbstractApplicationInterface::requestTournamentReset,
            controller,&AbstractGameController::handleResetTournament);
    QObject::connect(controller,&AbstractGameController::requestResetTournament,
            modelsService,&AbstractModelsService::resetDartsScoreTournament);
    QObject::connect(modelsService,&AbstractModelsService::tournamentResetSuccess,
            controller,&AbstractGameController::isReset);
    QObject::connect(controller,&AbstractDartsController::isReset,
            application,&AbstractApplicationInterface::dartsControllerIsReset);
    /*
         * Add point
         */
    QObject::connect(application,&AbstractApplicationInterface::sendDartsMultiAttemptScore,
            controller,&AbstractDartsScoreController::handleAndProcessUserInput);
    QObject::connect(controller,&AbstractDartsScoreController::requestAddDartsScore,
            modelsService,&AbstractModelsService::addDartsScore);
    QObject::connect(modelsService,&AbstractModelsService::scoreAddedToDataContext,
            controller,&AbstractDartsScoreController::handleScoreAddedToDataContext);
    QObject::connect(controller,&AbstractDartsScoreController::scoreAddedSuccess,
            application,&AbstractApplicationInterface::dartsControllerAddedDartsMultiAttemptScore);
    QObject::connect(application,&AbstractApplicationInterface::requestControllerState,
            controller,&AbstractGameController::handleRequestFromUI);
    /*
         * Controller remove has removed scores
         */
    QObject::connect(controller,&AbstractDartsScoreController::scoreRemoved,
            application,&AbstractApplicationInterface::dartsControllerRemovedMultiAttemptScore);
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
    QObject::connect(controller,&AbstractDartsScoreController::revealDartsScore,
            modelsService,&AbstractModelsService::revealScore);
    QObject::connect(modelsService,&AbstractModelsService::revealDartsScoreSuccess,
            controller,&AbstractDartsScoreController::redoSuccess);
}
