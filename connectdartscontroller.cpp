#include "connectdartscontroller.h"

void ConnectDartsController::connectController(AbstractGameController *controller, AbstractApplicationInterface *application, AbstractDartsModelsContext *modelsService, AbstractRouteByDisplayHint *routeService)
{
    auto dartsScorecontroller = dynamic_cast<AbstractDartsController*>(controller);
    // Send tournament metadata
    QObject::connect(application,&AbstractApplicationInterface::requestCurrentTournamentId,
            dartsScorecontroller,&AbstractDartsController::handleRequestForCurrentTournamentMetaData);
    QObject::connect(dartsScorecontroller,&AbstractDartsController::sendCurrentTournamentId,
            modelsService,&AbstractDartsModelsContext::createDartsMetaData);
    // Controller requests indexes and playerscores
    QObject::connect(dartsScorecontroller,&AbstractDartsController::requestDartsTournamentIndexes,
            modelsService,&AbstractDartsModelsContext::createIndexes);
    QObject::connect(modelsService,&AbstractDartsModelsContext::sendIndexesAsJson,
            dartsScorecontroller,&AbstractDartsController::initializeControllerIndexes);
    // Controller request player details
    QObject::connect(dartsScorecontroller,&AbstractDartsController::requestTournamentAssignedPlayerDetails,
                     modelsService,&AbstractDartsModelsContext::getPlayerDetails);
    QObject::connect(modelsService,&AbstractDartsModelsContext::sendAssignedPlayerDetails,
                     dartsScorecontroller,&AbstractDartsController::initializePlayerDetails);
    // Get input score model values
    QObject::connect(dartsScorecontroller,&AbstractDartsController::requestTournamentDartsScores,
                     modelsService,&AbstractDartsModelsContext::getPlayerInputs);
    QObject::connect(modelsService,&AbstractDartsModelsContext::sendInputs,
                     dartsScorecontroller,&AbstractDartsController::initializeDartsScores);
    QObject::connect(dartsScorecontroller,&AbstractDartsController::requestTournamentWinnerIdAndName,
                     modelsService,&AbstractDartsModelsContext::getTournamentWinnerDetails);
    QObject::connect(modelsService,&AbstractDartsModelsContext::sendWinnerDetails,
                     dartsScorecontroller,&AbstractDartsController::initializeWinnerDetails);
    QObject::connect(dartsScorecontroller,&AbstractDartsController::controllerInitialized,
                     routeService,&AbstractRouteByDisplayHint::determineDartsScoreRouteByDisplayHint);
    /*
     * UI requests multi attempt playerscores
     */
    QObject::connect(application,&AbstractApplicationInterface::requestDartsScores,
            dartsScorecontroller,&AbstractDartsController::createOrderedDartsScores);
    QObject::connect(dartsScorecontroller,&AbstractDartsController::sendDartsScores,
            application,&AbstractApplicationInterface::sendOrderedDartsScores);
    /*
         * Wake up controller
         */
    QObject::connect(application,&AbstractApplicationInterface::requestWakeUp,
            dartsScorecontroller,&AbstractGameController::beginInitialize);
    /*
         * Controller needs to inform external context about its state
         */
    QObject::connect(dartsScorecontroller,&AbstractDartsController::controllerIsStopped,
            application,&AbstractApplicationInterface::controllerIsStopped);
    QObject::connect(dartsScorecontroller,&AbstractDartsController::controllerInitializedAndReady,
            application,&AbstractApplicationInterface::dartsScoreControllerIsReady);
    QObject::connect(dartsScorecontroller,&AbstractDartsController::awaitsInput,
            application,&AbstractApplicationInterface::controllerAwaitsInput);
    QObject::connect(dartsScorecontroller,&AbstractDartsController::winnerDeclared,
            modelsService,&AbstractDartsModelsContext::setDartsTournamentWinner);
    QObject::connect(modelsService,&AbstractDartsModelsContext::setDartsTournamentWinnerSucces,
                     dartsScorecontroller,&AbstractDartsController::winnerDetermined);
    QObject::connect(dartsScorecontroller,&AbstractDartsController::winnerDetermined,
                     application,&AbstractApplicationInterface::controllerHasDeclaredAWinner);
    /*
         * Start/stop game
         */
    QObject::connect(application,&AbstractApplicationInterface::requestStartGame,
            dartsScorecontroller,&AbstractGameController::start);
    QObject::connect(dartsScorecontroller,&AbstractDartsController::awaitsInput,
                     application,&AbstractApplicationInterface::controllerAwaitsInput);
    QObject::connect(application,&AbstractApplicationInterface::requestStopGame,
            dartsScorecontroller,&AbstractGameController::stop);
    /*
         * Reset tournament
         */
    QObject::connect(application,&AbstractApplicationInterface::requestTournamentReset,
            dartsScorecontroller,&AbstractGameController::handleResetTournament);
    QObject::connect(dartsScorecontroller,&AbstractGameController::requestResetTournament,
            modelsService,&AbstractDartsModelsContext::resetDartsPointTournament);
    QObject::connect(modelsService,&AbstractDartsModelsContext::tournamentResetSuccess,
            dartsScorecontroller,&AbstractGameController::resetSucces);
    QObject::connect(dartsScorecontroller,&AbstractDartsController::resetSucces,
            application,&AbstractApplicationInterface::dartsControllerIsReset);
    /*
         * Add point
         */
    QObject::connect(application,&AbstractApplicationInterface::sendDartsScore,
            dartsScorecontroller,&AbstractDartsController::handleAndProcessUserInput);
    QObject::connect(dartsScorecontroller,&AbstractDartsController::requestAddDartsScore,
            modelsService,&AbstractDartsModelsContext::addInput);
    QObject::connect(modelsService,&AbstractDartsModelsContext::scoreAddedToDataContext,
            dartsScorecontroller,&AbstractDartsController::handleScoreAddedToDataContext);
    QObject::connect(dartsScorecontroller,&AbstractDartsController::scoreAddedSuccess,
            application,&AbstractApplicationInterface::addedDartsScore);
    QObject::connect(application,&AbstractApplicationInterface::requestControllerState,
            dartsScorecontroller,&AbstractGameController::handleRequestFromUI);
    /*
         * Controller remove has removed scores
         */
    QObject::connect(dartsScorecontroller,&AbstractDartsController::scoreRemoved,
            application,&AbstractApplicationInterface::dartsControllerRemovedScore);
    /*
         * Undo/redo
         */
    QObject::connect(application,&AbstractApplicationInterface::requestUndo,
            dartsScorecontroller,&AbstractDartsController::undoTurn);
    QObject::connect(dartsScorecontroller,&AbstractDartsController::hideInput,
            modelsService,&AbstractDartsModelsContext::hideInput);
    QObject::connect(modelsService,&AbstractDartsModelsContext::hideInputSuccess,
            dartsScorecontroller,&AbstractDartsController::undoSuccess);
    QObject::connect(application,&AbstractApplicationInterface::requestRedo,
            dartsScorecontroller,&AbstractDartsController::redoTurn);
    QObject::connect(dartsScorecontroller,&AbstractDartsController::revealInput,
            modelsService,&AbstractDartsModelsContext::revealInput);
    QObject::connect(modelsService,&AbstractDartsModelsContext::revealInputSuccess,
            dartsScorecontroller,&AbstractDartsController::redoSuccess);
}
