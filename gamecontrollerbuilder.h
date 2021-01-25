#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include "IControllerBuilder.h"
#include "abstractgamecontroller.h"
#include "localftpcontroller.h"
// Include services
#include "pointlogisticmanager.h"
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

    enum ContextMode {
        LocalContext = 0x7,
        RemoteContext = 0x8
    };

    AbstractGameController *assembleFTPGameController(const QVector<QUuid>& tournamentIdAndWinner,
                                                      const QVector<int>& values,
                                                      const QVector<QUuid>& userIds,
                                                      const QVector<QString>& userNames,
                                                      AbstractApplicationInterface* applicationInterface,
                                                      AbstractModelsContextInterface* modelsContext) override
    {
        auto tournament = tournamentIdAndWinner[0];
        auto winner = tournamentIdAndWinner[1];
        auto keyPoint = values[1];
        auto numberOfThrows = values[2];
        auto terminalKeyCode = values[3];
        auto inputMode = values[4];
        auto indexes = values.mid(5,5);
        auto userScores = values.mid(10);
        auto playersCount = userIds.count();
        AbstractGameController* controller = nullptr;
        if(inputMode == InputModes::PointMode)
        {
            controller = LocalFTPController::createInstance(tournament,keyPoint)
                    ->setPointLogisticInterface(PointLogisticManager::createInstance(numberOfThrows,terminalKeyCode))
                    ->setScoreCalculator(PointScoreCalculator::createInstance())
                    ->setInputValidator(PointValidator::createInstance(terminalKeyCode))
                    ->setIndexController(PointIndexController::createInstance(numberOfThrows,playersCount,indexes))
                    ->setScoreController(FTPScoreController::createInstance(userIds,userNames,userScores,winner));
        }
        else if(inputMode == InputModes::ScoreMode)
        {
            controller = LocalFTPController::createInstance(tournament,keyPoint)
                    ->setPointLogisticInterface(PointLogisticManager::createInstance(numberOfThrows,terminalKeyCode))
                    ->setScoreCalculator(new ScoreCalculator())
                    ->setInputValidator(ScoreValidator::createInstance(terminalKeyCode))
                    ->setIndexController(ScoreIndexController::createInstance(playersCount,indexes))
                    ->setScoreController(FTPScoreController::createInstance(userIds,userNames,userScores,winner));
        }
        connectFTPControllerWithInterfaces(controller,applicationInterface,modelsContext);
        emit sendController(controller);
        return controller;
    }
    virtual void determineTournamentGameMode(const QUuid &tournament, const int &gameMode) override
    {
        if(gameMode == GameModes::FirstToPost)
            emit requestFTPDetails(tournament);
    }

private:
    void connectFTPControllerWithInterfaces(AbstractGameController* controller,
                                            AbstractApplicationInterface* applicationInterface,
                                            AbstractModelsContextInterface* modelsContext)
    {
        /*
         * Establish communication between controller and UI
         */
        QObject::connect(controller,&AbstractGameController::transmitResponse,
                applicationInterface,&AbstractApplicationInterface::transmitResponse);
        /*
         * Send tournament metadata
         */
        connect(applicationInterface,&AbstractApplicationInterface::requestTournamentMetaData,
                controller,&AbstractGameController::handleRequestForCurrentTournamentMetaData);
        connect(controller,&AbstractGameController::requestFTPTournamentMetaData,
                modelsContext,&AbstractModelsContextInterface::handleRequestForFTPMetaData);
        /*
         * Setup request transmitting multithrow playerscores
         */
        connect(applicationInterface,&AbstractApplicationInterface::requestMultiThrowPlayerScores,
                controller,&AbstractGameController::handleRequestForMultiThrowPlayerScores);
        connect(controller,&AbstractGameController::requestTransmitPlayerScores,
                modelsContext,&AbstractModelsContextInterface::handleTransmitPlayerScores);
        /*
         * Setup request transmitting singlethrow playerscores
         */
        connect(applicationInterface,&AbstractApplicationInterface::requestSingleThrowPlayerScores,
                controller,&AbstractGameController::handleRequestForSingleThrowPlayerScores);
        /*
         * Wake up controller
         */
        connect(applicationInterface,&AbstractApplicationInterface::requestWakeUp,
                controller,&AbstractGameController::handleWakeUpRequest);
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
                modelsContext,&AbstractModelsContextInterface::handleResetTournament);
        connect(modelsContext,&AbstractModelsContextInterface::tournamentResetSuccess,
                controller,&AbstractGameController::handleTournamentResetSuccess);
        /*
         * Add point
         */
        connect(applicationInterface,&AbstractApplicationInterface::requestControllerState,
                controller,&AbstractGameController::handleRequestFromUI);
        connect(applicationInterface,&AbstractApplicationInterface::sendPoint,
                controller,&AbstractGameController::handleAndProcessUserInput);
        connect(controller,&AbstractGameController::requestAddScore,
                modelsContext,&AbstractModelsContextInterface::handleAddScore);
        connect(modelsContext,&AbstractModelsContextInterface::scoreAddedToDataContext,
                controller,&AbstractGameController::handleScoreAddedToDataContext);
        /*
         * Undo/redo
         */
        connect(applicationInterface,&AbstractApplicationInterface::requestUndo,
                controller,&AbstractGameController::undoTurn);
        connect(applicationInterface,&AbstractApplicationInterface::requestRedo,
                controller,&AbstractGameController::redoTurn);
        connect(controller,&AbstractGameController::requestSetModelHint,
                modelsContext,&AbstractModelsContextInterface::handleRequestSetScoreHint);
        connect(modelsContext,&AbstractModelsContextInterface::scoreHintUpdated,
                controller,&AbstractGameController::handleScoreHintUpdated);
        /*
         * Controller request tournament persistence
         */
        connect(applicationInterface,&AbstractApplicationInterface::requestPersistTournament,
                controller,&AbstractGameController::handleRequestPersistCurrentState);
        connect(controller,&AbstractGameController::requestPersistModelState,
                modelsContext,&AbstractModelsContextInterface::handleRequestPersistTournamentState);
        connect(modelsContext,&AbstractModelsContextInterface::tournamentModelsStatePersisted,
                controller,&AbstractGameController::handlePersistModelStateDone);
    }
};


#endif // GAMEBUILDER_H