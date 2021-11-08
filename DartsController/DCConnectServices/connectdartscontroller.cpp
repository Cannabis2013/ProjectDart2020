#include "DartsController/DCConnectServices/connectdartscontroller.h"

void ConnectDartsController::connectController(AbstractGameController *controller,
                                               AbstractApplicationInterface *application,
                                               AbstractDartsModelsContext *modelsContext,
                                               AbstractRouteByHint *routeService)
{
    auto dartscontroller = dynamic_cast<AbstractDartsController*>(controller);
    // Send tournament metadata
    QObject::connect(application,&AbstractApplicationInterface::requestCurrentTournamentId,
            dartscontroller,&AbstractDartsController::sendTournamentId);
    QObject::connect(dartscontroller,&AbstractDartsController::sendCurrentTournamentId,
            modelsContext,&AbstractDartsModelsContext::createDartsMetaData);
    // Controller request index, input, player and winner values
    QObject::connect(dartscontroller,&AbstractDartsController::sendInitValues,
            modelsContext,&AbstractDartsModelsContext::createDartsValuesJson);
    QObject::connect(modelsContext,&AbstractDartsModelsContext::dartsValues,
            dartscontroller,&AbstractDartsController::init);
    // Request ordered inputs
    QObject::connect(dartscontroller,&AbstractDartsController::requestOrderedInputs,
                     modelsContext,&AbstractDartsModelsContext::getOrderedInputs);
    QObject::connect(modelsContext,&AbstractDartsModelsContext::sendOrderedInputs,
                     dartscontroller,&AbstractDartsController::sendOrderedInputs);
    // Controller is initialized
    QObject::connect(dartscontroller,&AbstractDartsController::initialized,
                     routeService,&AbstractRouteByHint::routeByInputHint);
    // UI requests singleattempt scores
    QObject::connect(application,&AbstractApplicationInterface::requestDartsScores,
            dartscontroller,&AbstractDartsController::createScores);
    QObject::connect(dartscontroller,&AbstractDartsController::sendDartsScores,
            application,&AbstractApplicationInterface::sendDartsScores);
    // Wake up controller
    QObject::connect(application,&AbstractApplicationInterface::requestWakeUp,
            dartscontroller,&AbstractGameController::startInit);
    // Controller needs to notify external context about its state
    QObject::connect(dartscontroller,&AbstractDartsController::controllerIsStopped,
            application,&AbstractApplicationInterface::controllerStopped);
    QObject::connect(dartscontroller,&AbstractDartsController::ready,
                     application,&AbstractApplicationInterface::controllerReady);
    QObject::connect(dartscontroller,&AbstractDartsController::winnerDeclared,
            modelsContext,&AbstractDartsModelsContext::setDartsTournamentWinner);
    QObject::connect(modelsContext,&AbstractDartsModelsContext::setDartsTournamentWinnerSucces,
                     dartscontroller,&AbstractDartsController::winnerDetermined);
    QObject::connect(dartscontroller,&AbstractDartsController::winnerDetermined,
                     application,&AbstractApplicationInterface::winnerFound);
    // Start/stop game
    QObject::connect(application,&AbstractApplicationInterface::requestStartGame,
                     dartscontroller,&AbstractDartsController::createTurnValuesJson);
    QObject::connect(dartscontroller,&AbstractDartsController::sendTurnValues,
                     application,&AbstractApplicationInterface::updateDartsTurnValues);
    QObject::connect(application,&AbstractApplicationInterface::requestStopGame,
            dartscontroller,&AbstractGameController::controllerIsStopped);
    QObject::connect(application,&AbstractApplicationInterface::dartsNextTurn,
                     dartscontroller,&AbstractDartsController::createIndexJson);
    // Reset tournament
    QObject::connect(application,&AbstractApplicationInterface::requestTournamentReset,
            dartscontroller,&AbstractGameController::reset);
    QObject::connect(dartscontroller,&AbstractGameController::requestResetTournament,
            modelsContext,&AbstractDartsModelsContext::resetTournament);
    QObject::connect(modelsContext,&AbstractDartsModelsContext::tournamentResetSuccess,
            dartscontroller,&AbstractGameController::resetSucces);
    QObject::connect(dartscontroller,&AbstractDartsController::resetSucces,
            application,&AbstractApplicationInterface::dartsControllerIsReset);
    // Process and persist player input
    QObject::connect(application,&AbstractApplicationInterface::addUserInput,
                     dartscontroller,&AbstractDartsController::handleUserInput);
    QObject::connect(dartscontroller,&AbstractDartsController::addInputToDbContext,
                     modelsContext,&AbstractDartsModelsContext::addInput);
    QObject::connect(modelsContext,&AbstractDartsModelsContext::inputAdded,
                     dartscontroller,&AbstractDartsController::createScoreJson);
    QObject::connect(dartscontroller,&AbstractDartsController::updatePlayerScore,
                     application,&AbstractApplicationInterface::sendDartsScore);
    QObject::connect(dartscontroller,&AbstractDartsController::updateTournamentIndex,
                     modelsContext,&AbstractDartsModelsContext::updateTournamentIndex);
    QObject::connect(modelsContext,&AbstractDartsModelsContext::tournamentIndexUpdated,
                     dartscontroller,&AbstractDartsController::createJsonResponse);
    // External context requests state from controller
    QObject::connect(application,&AbstractApplicationInterface::requestControllerState,
                     dartscontroller,&AbstractGameController::requestStatus);
    // Undo/redo
    QObject::connect(application,&AbstractApplicationInterface::dartsUndo,
                     dartscontroller,&AbstractDartsController::undoTurn);
    QObject::connect(dartscontroller,&AbstractDartsController::hideInput,
                     modelsContext,&AbstractDartsModelsContext::hideInput);
    QObject::connect(modelsContext,&AbstractDartsModelsContext::hideInputSuccess,
                     dartscontroller,&AbstractDartsController::createScoreJson);
    QObject::connect(application,&AbstractApplicationInterface::dartsRedo,
                     dartscontroller,&AbstractDartsController::redoTurn);
    QObject::connect(dartscontroller,&AbstractDartsController::revealInput,
                     modelsContext,&AbstractDartsModelsContext::revealInput);
    QObject::connect(modelsContext,&AbstractDartsModelsContext::revealInputSuccess,
                     dartscontroller,&AbstractDartsController::createScoreJson);
}
