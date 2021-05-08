#include "connectdartssinglescorecontroller.h"

void ConnectDartsSingleScoreController::service(AbstractDartsScoreController *controller, AbstractApplicationInterface *application, AbstractModelsService *modelsService)
{
    // Send tournament metadata
    QObject::connect(application,&AbstractApplicationInterface::requestCurrentTournamentId,
            controller,&AbstractDartsScoreController::handleRequestForCurrentTournamentMetaData);
    QObject::connect(controller,&AbstractDartsScoreController::sendCurrentTournamentId,
            modelsService,&AbstractModelsService::assembleDartsTournamentDataFromId);
    // Controller requests indexes and playerscores
    QObject::connect(controller,&AbstractDartsScoreController::requestDartsTournamentIndexes,
            modelsService,&AbstractModelsService::assembleDartsPointIndexes);
    QObject::connect(modelsService,&AbstractModelsService::sendDartsPointIndexesAsJson,
            controller,&AbstractDartsController::initializeControllerIndexes);
    QObject::connect(controller,&AbstractDartsScoreController::requestTournamentAssignedPlayerDetails,
                     modelsService,&AbstractModelsService::assembleAssignedPlayerEntities);
    QObject::connect(modelsService,&AbstractModelsService::sendAssignedPlayerIdsAndNamesAsJson,
                     controller,&AbstractDartsScoreController::initializeControllerPlayerDetails);
    QObject::connect(controller,&AbstractDartsScoreController::requestTournamentDartsScores,
                     modelsService,&AbstractModelsService::assembleAssignedPlayerPoints);
    QObject::connect(modelsService,&AbstractModelsService::sendTournamentDartsPointsAsJson,
                     controller,&AbstractDartsScoreController::initializeControllerDartsScores);
    QObject::connect(controller,&AbstractDartsScoreController::requestTournamentWinnerIdAndName,
                     modelsService,&AbstractModelsService::assembleDartsTournamentWinnerIdAndName);
    QObject::connect(modelsService,&AbstractModelsService::sendDartsTournamentWinnerIdAndName,
                     controller,&AbstractDartsScoreController::initializeControllerWinnerIdAndName);
    /*
     * Controller requests transmitting singlethrow playerscores
     */
    QObject::connect(application,&AbstractApplicationInterface::requestMultiAttemptPlayerScores,
            controller,&AbstractDartsScoreController::assembleSingleAttemptDartsScores);
    QObject::connect(controller,&AbstractDartsScoreController::sendSingleAttemptDartsScores,
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
    QObject::connect(controller,&AbstractDartsScoreController::dartsSingleScoreControllerIsInitialized,
            application,&AbstractApplicationInterface::dartsSingleScoreControllerIsInitialized);
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
            application,&AbstractApplicationInterface::dartsControllerIsReset);
    /*
         * Add point
         */
    QObject::connect(application,&AbstractApplicationInterface::sendSingleAttemptPlayerInput,
            controller,&AbstractGameController::handleAndProcessUserInput);
    QObject::connect(controller,&AbstractDartsScoreController::requestAddDartsScore,
            modelsService,&AbstractModelsService::addDartsPoint);
    QObject::connect(modelsService,&AbstractModelsService::scoreAddedToDataContext,
            controller,&AbstractDartsScoreController::handleScoreAddedToDataContext);
    QObject::connect(controller,&AbstractDartsScoreController::scoreAddedSuccess,
            application,&AbstractApplicationInterface::dartsControllerAddedAndPersistedScore);
    QObject::connect(application,&AbstractApplicationInterface::requestControllerState,
            controller,&AbstractGameController::handleRequestFromUI);
    /*
         * Controller remove has removed scores
         */
    QObject::connect(controller,&AbstractDartsScoreController::scoreRemoved,
            application,&AbstractApplicationInterface::dartsControllerRemovedSingleAttemptPoint);
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
}
