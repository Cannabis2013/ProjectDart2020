#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include "IControllerBuilder.h"
#include "AbstractFtpController.h"
#include "localftpcontroller.h"
// Include services
#include "pointlogisticcontroller.h"
#include "scorelogisticcontroller.h"
#include "pointScoreCalculator.h"
#include "scorecalculator.h"
#include "pointvalidator.h"
#include "ScoreValidator.h"
#include "abstractcontrollerbuilder.h"
#include "ftpscorecontroller.h"
#include "PointIndexController.h"
#include "scoreindexcontroller.h"

class GameControllerBuilder : public AbstractControllerBuilder
{
    // IControllerBuilder interface
public:
    enum GameModes {
        FirstToPost = 0x1,
        RoundBased =0x2,
        CircularDart = 0x3
    };

    enum InputModes {
        PointMode = 0x5,
        ScoreMode = 0x6
    };

    enum DisplayHint
    {
        SingleColumn = 0x4,
        MultiColumn = 0x8
    };

    enum ContextMode {
        LocalContext = 0x7,
        RemoteContext = 0x8
    };

    AbstractGameController *assembleFTPGameController(const QUuid& tournamentId,
                                                      const QUuid& winnerId,
                                                      const QVector<int>& tournamentKeyValues,
                                                      AbstractApplicationInterface* applicationInterface,
                                                      AbstractModelsContext* modelsContext) override
    {
        auto keyPoint = tournamentKeyValues[0];
        auto attempts = tournamentKeyValues[1];
        auto terminalKeyCode = tournamentKeyValues[2];
        auto inputMode = tournamentKeyValues[3];
        AbstractFtpController* controller = nullptr;
        if(inputMode == InputModes::PointMode)
        {
            controller = assembleFtpPointBasedController(tournamentId,winnerId,keyPoint,
                                                         terminalKeyCode,attempts);
        }
        else if(inputMode == InputModes::ScoreMode)
        {
            controller = assembleFtpScoreBasedController(tournamentId,winnerId,
                                                         keyPoint,terminalKeyCode,
                                                         attempts);
        }
        connectFTPController(controller,applicationInterface,modelsContext);
        emit sendController(controller);
        return controller;
    }
    virtual void determineTournamentGameMode(const QUuid &tournament, const int &gameMode) override
    {
        if(gameMode == GameModes::FirstToPost)
            emit requestFTPDetails(tournament);
    }

private:
    AbstractFtpController* assembleFtpPointBasedController(const QUuid& tournament,
                                                            const QUuid& winnerId,
                                                            const int& keyPoint,
                                                            const int& terminalKeyCode,
                                                            const int& attempts)
    {
        AbstractFtpController* controller = LocalFtpController::createInstance(tournament)
                ->setLogisticInterface(PointLogisticController::createInstance(attempts,
                                                                                 terminalKeyCode))
                ->setScoreCalculator(PointScoreCalculator::createInstance())
                ->setInputValidator(PointValidator::createInstance(terminalKeyCode))
                ->setIndexController(PointIndexController::createInstance(attempts))
                ->setScoreController(FTPScoreController::createInstance(keyPoint,
                                                                        winnerId));
        return controller;
    }
    AbstractFtpController* assembleFtpScoreBasedController(const QUuid& tournament,
                                                            const QUuid& winnerId,
                                                            const int& keyPoint,
                                                            const int& terminalKeyCode,
                                                            const int& attempts)
    {
        AbstractFtpController* controller = LocalFtpController::createInstance(tournament)
                ->setLogisticInterface(ScoreLogisticController::createInstance(attempts,terminalKeyCode))
                ->setScoreCalculator(new ScoreCalculator())
                ->setInputValidator(ScoreValidator::createInstance(terminalKeyCode))
                ->setIndexController(ScoreIndexController::createInstance())
                ->setScoreController(FTPScoreController::createInstance(keyPoint,
                                                                        winnerId));
        return controller;
    }
    void connectFTPController(AbstractFtpController* controller,
                                            AbstractApplicationInterface*  applicationInterface,
                                            AbstractModelsContext* modelsContext)
    {
        /*
         * Establish communication between controller and UI
         */
        QObject::connect(controller,&AbstractFtpController::transmitResponse,
                applicationInterface,&AbstractApplicationInterface::transmitResponse);
        /*
         * Send tournament metadata
         */
        connect(applicationInterface,&AbstractApplicationInterface::requestCurrentTournamentId,
                controller,&AbstractFtpController::handleRequestForCurrentTournamentMetaData);
        connect(controller,&AbstractFtpController::sendCurrentTournamentId,
                modelsContext,&AbstractModelsContext::assembleFTPMetaDataFromId);
        /*
         * Controller requests indexes and playerscores
         */
        connect(controller,&AbstractFtpController::requestFtpIndexesAndScores,
                modelsContext,&AbstractModelsContext::assembleFtpIndexesAndScores);
        connect(modelsContext,&AbstractModelsContext::sendFtpIndexesAndScoreEntities,
                controller,&AbstractFtpController::recieveFtpIndexesAndEntities);
        /*
         * Controller is initialized and ready
         */
        connect(controller,&AbstractFtpController::initializedAndAwaitsInput,
                applicationInterface,&AbstractApplicationInterface::FtpControllerInitializedAndReady);
        /*
         * Controller requests transmitting multithrow playerscores
         */
        connect(applicationInterface,&AbstractApplicationInterface::requestFTPScores,
                controller,&AbstractFtpController::handleRequestFtpPlayerScores);
        connect(controller,&AbstractFtpController::requestFTPScores,
                modelsContext,&AbstractModelsContext::handleRequestFtpScores);
        /*
         * Controller requests transmitting singlethrow playerscores
         */
        connect(applicationInterface,&AbstractApplicationInterface::requestSingleThrowPlayerScores,
                controller,&AbstractFtpController::handleRequestForSingleThrowPlayerScores);
        /*
         * Wake up controller
         */
        connect(applicationInterface,&AbstractApplicationInterface::requestWakeUp,
                controller,&AbstractGameController::initialize);
        /*
         * Start/stop game
         */
        connect(applicationInterface,&AbstractApplicationInterface::requestStartGame,
                controller,&AbstractGameController::start);
        connect(applicationInterface,&AbstractApplicationInterface::requestStopGame,
                controller,&AbstractGameController::stop);
        /*
         * Reset tournament
         */
        connect(applicationInterface,&AbstractApplicationInterface::requestTournamentReset,
                controller,&AbstractGameController::handleResetTournament);
        connect(controller,&AbstractGameController::requestResetTournament,
                modelsContext,&AbstractModelsContext::resetTournament);
        connect(modelsContext,&AbstractModelsContext::tournamentResetSuccess,
                controller,&AbstractGameController::handleTournamentResetSuccess);
        /*
         * Add point
         */
        connect(applicationInterface,&AbstractApplicationInterface::sendPoint,
                controller,&AbstractGameController::handleAndProcessUserInput);
        connect(controller,&AbstractFtpController::requestAddFtpScore,
                modelsContext,&AbstractModelsContext::addFtpScore);
        connect(modelsContext,&AbstractModelsContext::scoreAddedToDataContext,
                controller,&AbstractGameController::handleScoreAddedToDataContext);
        connect(applicationInterface,&AbstractApplicationInterface::requestControllerState,
                controller,&AbstractGameController::handleRequestFromUI);
        /*
         * Undo/redo
         */
        connect(applicationInterface,&AbstractApplicationInterface::requestUndo,
                controller,&AbstractGameController::undoTurn);
        connect(applicationInterface,&AbstractApplicationInterface::requestRedo,
                controller,&AbstractGameController::redoTurn);
        connect(controller,&AbstractGameController::requestSetModelHint,
                modelsContext,&AbstractModelsContext::setFtpScoreHint);
        connect(modelsContext,&AbstractModelsContext::scoreHintUpdated,
                controller,&AbstractGameController::handleScoreHintUpdated);
        /*
         * Controller request tournament persistence
         */
        connect(applicationInterface,&AbstractApplicationInterface::requestPersistTournament,
                controller,&AbstractGameController::handleRequestPersistCurrentState);
        connect(controller,&AbstractGameController::requestPersistModelState,
                modelsContext,&AbstractModelsContext::handleRequestPersistTournamentState);
    }
};


#endif // GAMEBUILDER_H
