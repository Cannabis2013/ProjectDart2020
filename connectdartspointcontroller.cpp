#include "connectdartspointcontroller.h"

void ConnectDartsPointController::connectController(AbstractGameController *controller,
                                                    AbstractApplicationInterface *application,
                                                    AbstractDartsModelsContext *modelsService, AbstractRouteByDisplayHint *routeService)
{
    auto dartsPointController = static_cast<AbstractDartsPointController*>(controller);
    // Send tournament metadata
    QObject::connect(application,&AbstractApplicationInterface::requestCurrentTournamentId,
            dartsPointController,&AbstractDartsPointController::handleRequestForCurrentTournamentMetaData);
    QObject::connect(dartsPointController,&AbstractDartsPointController::sendCurrentTournamentId,
            modelsService,&AbstractDartsModelsContext::createDartsMetaData);
    // Controller requests indexes and playerscores
    QObject::connect(dartsPointController,&AbstractDartsPointController::requestDartsTournamentIndexes,
            modelsService,&AbstractDartsModelsContext::createDartsPointIndexes);
    QObject::connect(modelsService,&AbstractDartsModelsContext::sendDartsPointIndexesAsJson,
            dartsPointController,&AbstractDartsController::initializeControllerIndexes);
    QObject::connect(dartsPointController,&AbstractDartsPointController::requestTournamentAssignedPlayerDetails,
                     modelsService,&AbstractDartsModelsContext::createAssignedPlayerEntities);
    QObject::connect(modelsService,&AbstractDartsModelsContext::sendAssignedPlayerIdsAndNamesAsJson,
                     dartsPointController,&AbstractDartsPointController::initializeControllerPlayerDetails);
    QObject::connect(dartsPointController,&AbstractDartsPointController::requestTournamentDartsPoints,
                     modelsService,&AbstractDartsModelsContext::createAssignedPlayerPoints);
    QObject::connect(modelsService,&AbstractDartsModelsContext::sendTournamentDartsPointsAsJson,
                     dartsPointController,&AbstractDartsPointController::initializeControllerDartsPoints);
    QObject::connect(dartsPointController,&AbstractDartsPointController::requestTournamentWinnerIdAndName,
                     modelsService,&AbstractDartsModelsContext::createDartsTournamentWinnerIdAndName);
    QObject::connect(modelsService,&AbstractDartsModelsContext::sendDartsTournamentWinnerIdAndName,
                     dartsPointController,&AbstractDartsPointController::initializeControllerWinnerIdAndName);
    /*
     * Route by displayhint
     */
    QObject::connect(dartsPointController,&AbstractDartsPointController::controllerInitialized,
            routeService,&AbstractRouteByDisplayHint::determineDartsPointRouteByDisplayHint);
    // Controller requests transmitting single attempt playerpoints
    QObject::connect(application,&AbstractApplicationInterface::requestOrderedDartsInputs,
            dartsPointController,&AbstractDartsPointController::requestOrderedDartsPoints);
    QObject::connect(dartsPointController,&AbstractDartsPointController::requestDartsPointsOrderedByIndexes,
            modelsService,&AbstractDartsModelsContext::getOrderedDartsPoints);
    QObject::connect(modelsService,&AbstractDartsModelsContext::sendOrderedDartsPoints,
            dartsPointController,&AbstractDartsPointController::handleOrderedDartsPoint);
    QObject::connect(dartsPointController,&AbstractDartsPointController::sendOrderedDartsPoints,
            application,&AbstractApplicationInterface::sendOrderedDartsPoints);
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
    QObject::connect(dartsPointController,&AbstractDartsController::awaitsInput,
            application,&AbstractApplicationInterface::controllerAwaitsInput);
    QObject::connect(dartsPointController,&AbstractDartsController::winnerDeclared,
            modelsService,&AbstractDartsModelsContext::setDartsTournamentWinner);
    QObject::connect(modelsService,&AbstractDartsModelsContext::setDartsTournamentWinnerSucces,
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
            modelsService,&AbstractDartsModelsContext::resetDartsPointTournament);
    QObject::connect(modelsService,&AbstractDartsModelsContext::tournamentResetSuccess,
            dartsPointController,&AbstractGameController::resetSucces);
    QObject::connect(dartsPointController,&AbstractDartsController::resetSucces,
            application,&AbstractApplicationInterface::dartsControllerIsReset);
    /*
         * Add point
         */
    QObject::connect(application,&AbstractApplicationInterface::sendDartsPoint,
            dartsPointController,&AbstractGameController::handleAndProcessUserInput);
    QObject::connect(dartsPointController,&AbstractDartsPointController::requestAddDartsPoint,
            modelsService,&AbstractDartsModelsContext::addDartsPoint);
    QObject::connect(modelsService,&AbstractDartsModelsContext::pointAddedToDataContext,
            dartsPointController,&AbstractDartsPointController::handlePointAddedToDataContext);
    QObject::connect(dartsPointController,&AbstractDartsPointController::dartsPointPersisted,
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
            modelsService,&AbstractDartsModelsContext::hideDartsPoint);
    QObject::connect(modelsService,&AbstractDartsModelsContext::hideDartsPointSuccess,
            dartsPointController,&AbstractDartsPointController::undoSuccess);
    QObject::connect(application,&AbstractApplicationInterface::requestRedo,
            dartsPointController,&AbstractDartsPointController::redoTurn);
    QObject::connect(dartsPointController,&AbstractDartsPointController::revealDartsPoint,
            modelsService,&AbstractDartsModelsContext::revealPoint);
    QObject::connect(modelsService,&AbstractDartsModelsContext::revealDartsPointSuccess,
            dartsPointController,&AbstractDartsPointController::redoSuccess);
}
