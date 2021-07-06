#include "connectdartsscorecontroller.h"

void ConnectDartsScoreController::connectController(AbstractGameController *controller, AbstractApplicationInterface *application, AbstractModelsService *modelsService, AbstractRouteDartsByDisplayHint *routeService)
{
    auto dartsScorecontroller = dynamic_cast<AbstractDartsScoreController*>(controller);
    // Send tournament metadata
    QObject::connect(application,&AbstractApplicationInterface::requestCurrentTournamentId,
            dartsScorecontroller,&AbstractDartsScoreController::handleRequestForCurrentTournamentMetaData);
    QObject::connect(dartsScorecontroller,&AbstractDartsScoreController::sendCurrentTournamentId,
            modelsService,&AbstractModelsService::createDartsTournamentDataFromId);
    // Controller requests indexes and playerscores
    QObject::connect(dartsScorecontroller,&AbstractDartsScoreController::requestDartsTournamentIndexes,
            modelsService,&AbstractModelsService::createDartsScoreIndexes);
    QObject::connect(modelsService,&AbstractModelsService::sendDartsScoreIndexesAsJson,
            dartsScorecontroller,&AbstractDartsController::initializeControllerIndexes);
    QObject::connect(dartsScorecontroller,&AbstractDartsScoreController::requestTournamentAssignedPlayerDetails,
                     modelsService,&AbstractModelsService::createAssignedPlayerEntities);
    QObject::connect(modelsService,&AbstractModelsService::sendAssignedPlayerIdsAndNamesAsJson,
                     dartsScorecontroller,&AbstractDartsScoreController::initializeControllerPlayerDetails);
    QObject::connect(dartsScorecontroller,&AbstractDartsScoreController::requestTournamentDartsScores,
                     modelsService,&AbstractModelsService::createAssignedPlayerScores);
    QObject::connect(modelsService,&AbstractModelsService::sendTournamentDartsScoresAsJson,
                     dartsScorecontroller,&AbstractDartsScoreController::initializeControllerDartsScores);
    QObject::connect(dartsScorecontroller,&AbstractDartsScoreController::requestTournamentWinnerIdAndName,
                     modelsService,&AbstractModelsService::createDartsTournamentWinnerIdAndName);
    QObject::connect(modelsService,&AbstractModelsService::sendDartsTournamentWinnerIdAndName,
                     dartsScorecontroller,&AbstractDartsScoreController::initializeControllerWinnerIdAndName);
    QObject::connect(dartsScorecontroller,&AbstractDartsScoreController::controllerInitialized,
                     routeService,&AbstractRouteDartsByDisplayHint::determineDartsScoreRouteByDisplayHint);
    /*
     * UI requests multi attempt playerscores
     */
    QObject::connect(application,&AbstractApplicationInterface::requestDartsScores,
            dartsScorecontroller,&AbstractDartsScoreController::createOrderedDartsScores);
    QObject::connect(dartsScorecontroller,&AbstractDartsScoreController::sendMultiAttemptDartsScores,
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
    QObject::connect(dartsScorecontroller,&AbstractDartsScoreController::controllerInitializedAndReady,
            application,&AbstractApplicationInterface::dartsScoreControllerIsReady);
    QObject::connect(dartsScorecontroller,&AbstractDartsController::awaitsInput,
            application,&AbstractApplicationInterface::controllerAwaitsInput);
    QObject::connect(dartsScorecontroller,&AbstractDartsController::winnerDeclared,
            modelsService,&AbstractModelsService::setDartsTournamentWinner);
    QObject::connect(modelsService,&AbstractModelsService::setDartsTournamentWinnerSucces,
                     dartsScorecontroller,&AbstractDartsScoreController::winnerDetermined);
    QObject::connect(dartsScorecontroller,&AbstractDartsScoreController::winnerDetermined,
                     application,&AbstractApplicationInterface::controllerHasDeclaredAWinner);
    /*
         * Start/stop game
         */
    QObject::connect(application,&AbstractApplicationInterface::requestStartGame,
            dartsScorecontroller,&AbstractGameController::start);
    QObject::connect(dartsScorecontroller,&AbstractDartsScoreController::awaitsInput,
                     application,&AbstractApplicationInterface::controllerAwaitsInput);
    QObject::connect(application,&AbstractApplicationInterface::requestStopGame,
            dartsScorecontroller,&AbstractGameController::stop);
    /*
         * Reset tournament
         */
    QObject::connect(application,&AbstractApplicationInterface::requestTournamentReset,
            dartsScorecontroller,&AbstractGameController::handleResetTournament);
    QObject::connect(dartsScorecontroller,&AbstractGameController::requestResetTournament,
            modelsService,&AbstractModelsService::resetDartsScoreTournament);
    QObject::connect(modelsService,&AbstractModelsService::tournamentResetSuccess,
            dartsScorecontroller,&AbstractGameController::resetSucces);
    QObject::connect(dartsScorecontroller,&AbstractDartsController::resetSucces,
            application,&AbstractApplicationInterface::dartsControllerIsReset);
    /*
         * Add point
         */
    QObject::connect(application,&AbstractApplicationInterface::sendDartsScore,
            dartsScorecontroller,&AbstractDartsScoreController::handleAndProcessUserInput);
    QObject::connect(dartsScorecontroller,&AbstractDartsScoreController::requestAddDartsScore,
            modelsService,&AbstractModelsService::addDartsScore);
    QObject::connect(modelsService,&AbstractModelsService::scoreAddedToDataContext,
            dartsScorecontroller,&AbstractDartsScoreController::handleScoreAddedToDataContext);
    QObject::connect(dartsScorecontroller,&AbstractDartsScoreController::scoreAddedSuccess,
            application,&AbstractApplicationInterface::addedDartsScore);
    QObject::connect(application,&AbstractApplicationInterface::requestControllerState,
            dartsScorecontroller,&AbstractGameController::handleRequestFromUI);
    /*
         * Controller remove has removed scores
         */
    QObject::connect(dartsScorecontroller,&AbstractDartsScoreController::scoreRemoved,
            application,&AbstractApplicationInterface::dartsControllerRemovedScore);
    /*
         * Undo/redo
         */
    QObject::connect(application,&AbstractApplicationInterface::requestUndo,
            dartsScorecontroller,&AbstractDartsScoreController::undoTurn);
    QObject::connect(dartsScorecontroller,&AbstractDartsScoreController::hideDartsScore,
            modelsService,&AbstractModelsService::hideDartsScore);
    QObject::connect(modelsService,&AbstractModelsService::hideDartsScoreSuccess,
            dartsScorecontroller,&AbstractDartsScoreController::undoSuccess);
    QObject::connect(application,&AbstractApplicationInterface::requestRedo,
            dartsScorecontroller,&AbstractDartsScoreController::redoTurn);
    QObject::connect(dartsScorecontroller,&AbstractDartsScoreController::revealDartsScore,
            modelsService,&AbstractModelsService::revealScore);
    QObject::connect(modelsService,&AbstractModelsService::revealDartsScoreSuccess,
            dartsScorecontroller,&AbstractDartsScoreController::redoSuccess);
}
