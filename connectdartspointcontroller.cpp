#include "connectdartspointcontroller.h"

void ConnectDartsPointController::connectController(AbstractDartsController *controller,
                                                                 AbstractApplicationInterface *application,
                                                                 AbstractModelsService *modelsService, AbstractRouteDartsByDisplayHint *routeService)
{
    auto dartsPointController = static_cast<AbstractDartsPointController*>(controller);
    // Send tournament metadata
    QObject::connect(application,&AbstractApplicationInterface::requestCurrentTournamentId,
            dartsPointController,&AbstractDartsPointController::handleRequestForCurrentTournamentMetaData);
    QObject::connect(dartsPointController,&AbstractDartsPointController::sendCurrentTournamentId,
            modelsService,&AbstractModelsService::assembleDartsTournamentDataFromId);
    // Controller requests indexes and playerscores
    QObject::connect(dartsPointController,&AbstractDartsPointController::requestDartsTournamentIndexes,
            modelsService,&AbstractModelsService::assembleDartsPointIndexes);
    QObject::connect(modelsService,&AbstractModelsService::sendDartsPointIndexesAsJson,
            dartsPointController,&AbstractDartsController::initializeControllerIndexes);
    QObject::connect(dartsPointController,&AbstractDartsPointController::requestTournamentAssignedPlayerDetails,
                     modelsService,&AbstractModelsService::assembleAssignedPlayerEntities);
    QObject::connect(modelsService,&AbstractModelsService::sendAssignedPlayerIdsAndNamesAsJson,
                     dartsPointController,&AbstractDartsPointController::initializeControllerPlayerDetails);
    QObject::connect(dartsPointController,&AbstractDartsPointController::requestTournamentDartsPoints,
                     modelsService,&AbstractModelsService::assembleAssignedPlayerPoints);
    QObject::connect(modelsService,&AbstractModelsService::sendTournamentDartsPointsAsJson,
                     dartsPointController,&AbstractDartsPointController::initializeControllerDartsPoints);
    QObject::connect(dartsPointController,&AbstractDartsPointController::requestTournamentWinnerIdAndName,
                     modelsService,&AbstractModelsService::assembleDartsTournamentWinnerIdAndName);
    QObject::connect(modelsService,&AbstractModelsService::sendDartsTournamentWinnerIdAndName,
                     dartsPointController,&AbstractDartsPointController::initializeControllerWinnerIdAndName);
    /*
     * Route by displayhint
     */
    QObject::connect(dartsPointController,&AbstractDartsPointController::controllerInitialized,
            routeService,&AbstractRouteDartsByDisplayHint::determineDartsPointRouteByDisplayHint);
    // Controller requests transmitting single attempt playerpoints
    QObject::connect(application,&AbstractApplicationInterface::requestDartsSingleAttemptPoints,
            dartsPointController,&AbstractDartsPointController::handleRequestDartsPoints);
    QObject::connect(dartsPointController,&AbstractDartsPointController::requestDartsPointsOrderedByIndexes,
            modelsService,&AbstractModelsService::getOrderedDartsPoints);
    QObject::connect(modelsService,&AbstractModelsService::sendOrderedDartsPoints,
            dartsPointController,&AbstractDartsPointController::sendDartsPoints);
    QObject::connect(dartsPointController,&AbstractDartsPointController::sendDartsPoints,
            application,&AbstractApplicationInterface::sendDartsPoints);
    /*
         * Wake up controller
         */
    QObject::connect(application,&AbstractApplicationInterface::requestWakeUp,
            dartsPointController,&AbstractGameController::beginInitialize);
    /*
         * Controller needs to inform external context about its state
         */
    QObject::connect(dartsPointController,&AbstractDartsController::controllerIsStopped,
            application,&AbstractApplicationInterface::controllerIsStopped);
    QObject::connect(dartsPointController,&AbstractDartsPointController::controllerInitializedAndReady,
                     application,&AbstractApplicationInterface::dartsPointControllerIsReady);
    QObject::connect(dartsPointController,&AbstractDartsController::isReadyAndAwaitsInput,
            application,&AbstractApplicationInterface::controllerAwaitsInput);
    QObject::connect(dartsPointController,&AbstractDartsController::winnerDeclared,
            modelsService,&AbstractModelsService::setDartsTournamentWinner);
    QObject::connect(modelsService,&AbstractModelsService::setDartsTournamentWinnerSucces,
                     dartsPointController,&AbstractDartsPointController::winnerDetermined);
    QObject::connect(dartsPointController,&AbstractDartsPointController::winnerDetermined,
                     application,&AbstractApplicationInterface::controllerHasDeclaredAWinner);
    /*
         * Start/stop game
         */
    QObject::connect(application,&AbstractApplicationInterface::requestStartGame,
            dartsPointController,&AbstractGameController::start);
    QObject::connect(application,&AbstractApplicationInterface::requestStopGame,
            dartsPointController,&AbstractGameController::stop);
    /*
         * Reset tournament
         */
    QObject::connect(application,&AbstractApplicationInterface::requestTournamentReset,
            dartsPointController,&AbstractGameController::handleResetTournament);
    QObject::connect(dartsPointController,&AbstractGameController::requestResetTournament,
            modelsService,&AbstractModelsService::resetDartsPointTournament);
    QObject::connect(modelsService,&AbstractModelsService::tournamentResetSuccess,
            dartsPointController,&AbstractGameController::isReset);
    QObject::connect(dartsPointController,&AbstractDartsController::isReset,
            application,&AbstractApplicationInterface::dartsControllerIsReset);
    /*
         * Add point
         */
    QObject::connect(application,&AbstractApplicationInterface::sendDartsPoint,
            dartsPointController,&AbstractGameController::handleAndProcessUserInput);
    QObject::connect(dartsPointController,&AbstractDartsPointController::requestAddDartsPoint,
            modelsService,&AbstractModelsService::addDartsPoint);
    QObject::connect(modelsService,&AbstractModelsService::pointAddedToDataContext,
            dartsPointController,&AbstractDartsPointController::handlePointAddedToDataContext);
    QObject::connect(dartsPointController,&AbstractDartsPointController::pointAddedAndPersisted,
            application,&AbstractApplicationInterface::addedDartsPoint);
    QObject::connect(application,&AbstractApplicationInterface::requestControllerState,
            dartsPointController,&AbstractGameController::handleRequestFromUI);
    /*
         * Controller has removed scores
         */
    QObject::connect(dartsPointController,&AbstractDartsPointController::pointRemoved,
            application,&AbstractApplicationInterface::dartsControllerRemovedPoint);
    /*
         * Undo/redo
         */
    QObject::connect(application,&AbstractApplicationInterface::requestUndo,
            dartsPointController,&AbstractDartsPointController::undoTurn);
    QObject::connect(dartsPointController,&AbstractDartsPointController::hideDartsPoint,
            modelsService,&AbstractModelsService::hideDartsPoint);
    QObject::connect(modelsService,&AbstractModelsService::hideDartsPointSuccess,
            dartsPointController,&AbstractDartsPointController::undoSuccess);
    QObject::connect(application,&AbstractApplicationInterface::requestRedo,
            dartsPointController,&AbstractDartsPointController::redoTurn);
    QObject::connect(dartsPointController,&AbstractDartsPointController::revealDartsPoint,
            modelsService,&AbstractModelsService::revealPoint);
    QObject::connect(modelsService,&AbstractModelsService::revealDartsPointSuccess,
            dartsPointController,&AbstractDartsPointController::redoSuccess);
}
