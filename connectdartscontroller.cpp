#include "connectdartscontroller.h"

void ConnectDartsController::connectController(AbstractGameController *controller,
                                               AbstractApplicationInterface *application,
                                               AbstractDartsModelsContext *modelsService,
                                               AbstractRouteByDisplayHint *routeService)
{
    auto dartscontroller = dynamic_cast<AbstractDartsController*>(controller);
    // Send tournament metadata
    QObject::connect(application,&AbstractApplicationInterface::requestCurrentTournamentId,
            dartscontroller,&AbstractDartsController::handleRequestForCurrentTournamentMetaData);
    QObject::connect(dartscontroller,&AbstractDartsController::sendCurrentTournamentId,
            modelsService,&AbstractDartsModelsContext::createDartsMetaData);
    // Controller requests indexes and playerscores
    QObject::connect(dartscontroller,&AbstractDartsController::requestDartsTournamentIndexes,
            modelsService,&AbstractDartsModelsContext::createIndexes);
    QObject::connect(modelsService,&AbstractDartsModelsContext::sendIndexesAsJson,
            dartscontroller,&AbstractDartsController::initializeControllerIndexes);
    // Controller request player details
    QObject::connect(dartscontroller,&AbstractDartsController::requestTournamentAssignedPlayerDetails,
                     modelsService,&AbstractDartsModelsContext::getPlayerDetails);
    QObject::connect(modelsService,&AbstractDartsModelsContext::sendAssignedPlayerDetails,
                     dartscontroller,&AbstractDartsController::initializePlayerDetails);
    // Get input score model values
    QObject::connect(dartscontroller,&AbstractDartsController::requestScores,
                     modelsService,&AbstractDartsModelsContext::getPlayerInputs);
    QObject::connect(modelsService,&AbstractDartsModelsContext::sendInputs,
                     dartscontroller,&AbstractDartsController::initializeScores);
    QObject::connect(dartscontroller,&AbstractDartsController::requestWinnerDetails,
                     modelsService,&AbstractDartsModelsContext::getTournamentWinnerDetails);
    QObject::connect(modelsService,&AbstractDartsModelsContext::sendWinnerDetails,
                     dartscontroller,&AbstractDartsController::initializeWinnerDetails);
    // Request ordered inputs
    QObject::connect(application,&AbstractApplicationInterface::requestOrderedDartsInputs,
                     dartscontroller,&AbstractDartsController::getOrderedInputsWithTotalScores);
    QObject::connect(dartscontroller,&AbstractDartsController::requestOrderedInputs,
                     modelsService,&AbstractDartsModelsContext::getOrderedInputs);
    QObject::connect(modelsService,&AbstractDartsModelsContext::sendOrderedInputs,
                     dartscontroller,&AbstractDartsController::handleOrderedInputs);
    QObject::connect(dartscontroller,&AbstractDartsController::sendOrderedInputs,
                     application,&AbstractApplicationInterface::sendOrderedDartsInputs);
    // Controller is initialized
    QObject::connect(dartscontroller,&AbstractDartsController::initialized,
                     routeService,&AbstractRouteByDisplayHint::routeByHints);
    /*
     * UI requests singleattempt scores
     */
    QObject::connect(application,&AbstractApplicationInterface::requestDartsScores,
            dartscontroller,&AbstractDartsController::createDartsScores);
    QObject::connect(dartscontroller,&AbstractDartsController::sendDartsScores,
            application,&AbstractApplicationInterface::sendDartsScores);
    /*
         * Wake up controller
         */
    QObject::connect(application,&AbstractApplicationInterface::requestWakeUp,
            dartscontroller,&AbstractGameController::beginInitialize);
    /*
         * Controller needs to notify external context about its state
         */
    QObject::connect(dartscontroller,&AbstractDartsController::controllerIsStopped,
            application,&AbstractApplicationInterface::controllerIsStopped);
    QObject::connect(dartscontroller,&AbstractDartsController::controllerInitializedAndReady,
            application,&AbstractApplicationInterface::dartsControllerIsReady);
    QObject::connect(dartscontroller,&AbstractDartsController::awaitsInput,
            application,&AbstractApplicationInterface::controllerAwaitsInput);
    QObject::connect(dartscontroller,&AbstractDartsController::winnerDeclared,
            modelsService,&AbstractDartsModelsContext::setDartsTournamentWinner);
    QObject::connect(modelsService,&AbstractDartsModelsContext::setDartsTournamentWinnerSucces,
                     dartscontroller,&AbstractDartsController::winnerDetermined);
    QObject::connect(dartscontroller,&AbstractDartsController::winnerDetermined,
                     application,&AbstractApplicationInterface::controllerHasDeclaredAWinner);
    /*
         * Start/stop game
         */
    QObject::connect(application,&AbstractApplicationInterface::requestStartGame,
            dartscontroller,&AbstractGameController::start);
    QObject::connect(dartscontroller,&AbstractDartsController::awaitsInput,
                     application,&AbstractApplicationInterface::controllerAwaitsInput);
    QObject::connect(application,&AbstractApplicationInterface::requestStopGame,
            dartscontroller,&AbstractGameController::stop);
    /*
         * Reset tournament
         */
    QObject::connect(application,&AbstractApplicationInterface::requestTournamentReset,
            dartscontroller,&AbstractGameController::handleResetTournament);
    QObject::connect(dartscontroller,&AbstractGameController::requestResetTournament,
            modelsService,&AbstractDartsModelsContext::resetTournament);
    QObject::connect(modelsService,&AbstractDartsModelsContext::tournamentResetSuccess,
            dartscontroller,&AbstractGameController::resetSucces);
    QObject::connect(dartscontroller,&AbstractDartsController::resetSucces,
            application,&AbstractApplicationInterface::dartsControllerIsReset);
    /*
         * Add point
         */
    QObject::connect(application,&AbstractApplicationInterface::addUserInput,
            dartscontroller,&AbstractDartsController::handleUserInput);
    QObject::connect(dartscontroller,&AbstractDartsController::requestAddDartsScore,
            modelsService,&AbstractDartsModelsContext::addInput);
    QObject::connect(modelsService,&AbstractDartsModelsContext::inputModelAdded,
            dartscontroller,&AbstractDartsController::handleUserInputAdded);
    QObject::connect(dartscontroller,&AbstractDartsController::scoreAddedSuccess,
            application,&AbstractApplicationInterface::addedInput);
    // External context requests state from controller
    QObject::connect(application,&AbstractApplicationInterface::requestControllerState,
            dartscontroller,&AbstractGameController::handleRequestFromUI);
    /*
         * Controller remove has removed scores
         */
    QObject::connect(dartscontroller,&AbstractDartsController::scoreRemoved,
            application,&AbstractApplicationInterface::dartsInputRemoveSucces);
    /*
         * Undo/redo
         */
    QObject::connect(application,&AbstractApplicationInterface::requestUndo,
            dartscontroller,&AbstractDartsController::undoTurn);
    QObject::connect(dartscontroller,&AbstractDartsController::hideInput,
            modelsService,&AbstractDartsModelsContext::hideInput);
    QObject::connect(modelsService,&AbstractDartsModelsContext::hideInputSuccess,
            dartscontroller,&AbstractDartsController::undoSuccess);
    QObject::connect(application,&AbstractApplicationInterface::requestRedo,
            dartscontroller,&AbstractDartsController::redoTurn);
    QObject::connect(dartscontroller,&AbstractDartsController::revealInput,
            modelsService,&AbstractDartsModelsContext::revealInput);
    QObject::connect(modelsService,&AbstractDartsModelsContext::revealInputSuccess,
            dartscontroller,&AbstractDartsController::redoSuccess);
}
