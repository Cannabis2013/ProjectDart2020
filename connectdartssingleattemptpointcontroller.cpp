#include "connectdartssingleattemptpointcontroller.h"

AbstractDartsPointController *ConnectDartsSingleAttemptPointController::service(AbstractDartsPointController *controller,
                                                                   AbstractApplicationInterface *application,
                                                                   AbstractModelsService *modelsService)
{
    // Send tournament metadata
    QObject::connect(application,&AbstractApplicationInterface::requestCurrentTournamentId,
            controller,&AbstractDartsPointController::handleRequestForCurrentTournamentMetaData);
    QObject::connect(controller,&AbstractDartsPointController::sendCurrentTournamentId,
            modelsService,&AbstractModelsService::assembleDartsTournamentDataFromId);
    // Controller requests indexes and playerscores
    QObject::connect(controller,&AbstractDartsPointController::requestDartsTournamentIndexes,
            modelsService,&AbstractModelsService::assembleDartsPointIndexes);
    QObject::connect(modelsService,&AbstractModelsService::sendDartsPointIndexesAsJson,
            controller,&AbstractDartsController::initializeControllerIndexes);
    QObject::connect(controller,&AbstractDartsPointController::requestTournamentAssignedPlayerDetails,
                     modelsService,&AbstractModelsService::assembleAssignedPlayerEntities);
    QObject::connect(modelsService,&AbstractModelsService::sendAssignedPlayerIdsAndNamesAsJson,
                     controller,&AbstractDartsPointController::initializeControllerPlayerDetails);
    QObject::connect(controller,&AbstractDartsPointController::requestTournamentDartsPoints,
                     modelsService,&AbstractModelsService::assembleAssignedPlayerPoints);
    QObject::connect(modelsService,&AbstractModelsService::sendTournamentDartsPointsAsJson,
                     controller,&AbstractDartsPointController::initializeControllerDartsPoints);
    QObject::connect(controller,&AbstractDartsPointController::requestTournamentWinnerIdAndName,
                     modelsService,&AbstractModelsService::assembleDartsTournamentWinnerIdAndName);
    QObject::connect(modelsService,&AbstractModelsService::sendDartsTournamentWinnerIdAndName,
                     controller,&AbstractDartsPointController::initializeControllerWinnerIdAndName);
    QObject::connect(controller,&AbstractDartsPointController::dartsSingleAttemptControllerIsInitialized,
            application,&AbstractApplicationInterface::dartsSingleAttemptPointControllerIsInitialized);
    // Controller requests transmitting single attempt playerpoints
    QObject::connect(application,&AbstractApplicationInterface::requestDartsSingleAttemptPoints,
            controller,&AbstractDartsPointController::handleRequestDartsPoints);
    QObject::connect(controller,&AbstractDartsPointController::requestDartsPoints,
            modelsService,&AbstractModelsService::getOrderedDartsPoints);
    QObject::connect(modelsService,&AbstractModelsService::sendDartsSingleAttemptPoints,
            controller,&AbstractDartsPointController::sendDartsSingleAttemptPoints);
    QObject::connect(controller,&AbstractDartsPointController::sendDartsSingleAttemptPoints,
            application,&AbstractApplicationInterface::sendAssembledDartsSingleAttemptPoints);
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
    QObject::connect(controller,&AbstractDartsPointController::controllerIsInitializedAndReady,
                     application,&AbstractApplicationInterface::dartsSingleAttemptPointControllerIsReady);
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
            modelsService,&AbstractModelsService::resetDartsPointTournament);
    QObject::connect(modelsService,&AbstractModelsService::tournamentResetSuccess,
            controller,&AbstractGameController::isReset);
    QObject::connect(controller,&AbstractDartsController::isReset,
            application,&AbstractApplicationInterface::dartsControllerIsReset);
    /*
         * Add point
         */
    QObject::connect(application,&AbstractApplicationInterface::sendDartsSingleAttemptPoint,
            controller,&AbstractGameController::handleAndProcessUserInput);
    QObject::connect(controller,&AbstractDartsPointController::requestAddDartsPoint,
            modelsService,&AbstractModelsService::addDartsPoint);
    QObject::connect(modelsService,&AbstractModelsService::pointAddedToDataContext,
            controller,&AbstractDartsPointController::handlePointAddedToDataContext);
    QObject::connect(controller,&AbstractDartsPointController::pointAddedAndPersisted,
            application,&AbstractApplicationInterface::dartsControllerAddedDartsSingleAttemptPoint);
    QObject::connect(application,&AbstractApplicationInterface::requestControllerState,
            controller,&AbstractGameController::handleRequestFromUI);
    /*
         * Controller has removed scores
         */
    QObject::connect(controller,&AbstractDartsPointController::pointRemoved,
            application,&AbstractApplicationInterface::dartsControllerRemovedSingleAttemptPoint);
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
    QObject::connect(controller,&AbstractDartsPointController::revealDartsPoint,
            modelsService,&AbstractModelsService::revealPoint);
    QObject::connect(modelsService,&AbstractModelsService::revealDartsPointSuccess,
            controller,&AbstractDartsPointController::redoSuccess);
    return controller;
}

