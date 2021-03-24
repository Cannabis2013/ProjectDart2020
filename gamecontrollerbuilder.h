#ifndef GAMEBUILDER_H
#define GAMEBUILDER_H

#include "IControllerBuilder.h"
#include "abstractgamecontroller.h"
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

    AbstractGameController *assembleFTPGameController(const QVector<QUuid>& tournamentIdAndWinner,
                                                      const QVector<int>& values,
                                                      const QVector<QUuid>& userIds,
                                                      const QVector<QString>& userNames,
                                                      const QVector<int>& playerScores,
                                                      AbstractApplicationInterface* applicationInterface,
                                                      AbstractModelsContext* modelsContext) override
    {
        auto tournament = tournamentIdAndWinner[0];
        auto winner = tournamentIdAndWinner[1];
        auto keyPoint = values[1];
        auto attempts = values[2];
        auto terminalKeyCode = values[3];
        auto inputMode = values[4];
        auto indexes = values.mid(5,5);
        auto userScores = playerScores;
        AbstractGameController* controller = nullptr;
        if(inputMode == InputModes::PointMode)
        {
            controller = assembleFTPPointBasedController(tournament,winner,keyPoint,
                                                         terminalKeyCode,attempts,indexes,
                                                         userIds,userNames,userScores);
        }
        else if(inputMode == InputModes::ScoreMode)
        {
            controller = assembleFTPScoreBasedController(tournament,winner,keyPoint,
                                                         terminalKeyCode,attempts,indexes,userIds,
                                                         userNames,userScores);
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
    AbstractGameController* assembleFTPPointBasedController(const QUuid& tournament,
                                                            const QUuid& winnerId,
                                                            const int& keyPoint,
                                                            const int& terminalKeyCode,
                                                            const int& attempts,
                                                            const QVector<int>& indexes,
                                                            const QVector<QUuid>& playerIds,
                                                            const QVector<QString>& playerNames,
                                                            const QVector<int>& playerScores)
    {
        auto playersCount = playerIds.count();
        AbstractGameController* controller = LocalFTPController::createInstance(tournament)
                ->setLogisticInterface(PointLogisticController::createInstance(attempts,
                                                                                 terminalKeyCode))
                ->setScoreCalculator(PointScoreCalculator::createInstance())
                ->setInputValidator(PointValidator::createInstance(terminalKeyCode))
                ->setIndexController(PointIndexController::createInstance(attempts,
                                                                          playersCount,
                                                                          indexes))
                ->setScoreController(FTPScoreController::createInstance(playerIds,
                                                                        playerNames,
                                                                        playerScores,
                                                                        keyPoint,
                                                                        winnerId));
        return controller;
    }
    AbstractGameController* assembleFTPScoreBasedController(const QUuid& tournament,
                                                            const QUuid& winnerId,
                                                            const int& keyPoint,
                                                            const int& terminalKeyCode,
                                                            const int& attempts,
                                                            const QVector<int>& indexes,
                                                            const QVector<QUuid>& playerIds,
                                                            const QVector<QString>& playerNames,
                                                            const QVector<int>& playerScores)
    {
        auto playersCount = playerIds.count();
        AbstractGameController* controller = LocalFTPController::createInstance(tournament)
                ->setLogisticInterface(ScoreLogisticController::createInstance(attempts,terminalKeyCode))
                ->setScoreCalculator(new ScoreCalculator())
                ->setInputValidator(ScoreValidator::createInstance(terminalKeyCode))
                ->setIndexController(ScoreIndexController::createInstance(playersCount,
                                                                          indexes))
                ->setScoreController(FTPScoreController::createInstance(playerIds,
                                                                        playerNames,
                                                                        playerScores,
                                                                        keyPoint,winnerId));
        return controller;
    }
    void connectFTPControllerWithInterfaces(AbstractGameController* controller,
                                            AbstractApplicationInterface* applicationInterface,
                                            AbstractModelsContext* modelsContext)
    {
        /*
         * Establish communication between controller and UI
         */
        QObject::connect(controller,&AbstractGameController::transmitResponse,
                applicationInterface,&AbstractApplicationInterface::transmitResponse);
        /*
         * Send tournament metadata
         */
        connect(applicationInterface,&AbstractApplicationInterface::requestCurrentTournamentId,
                controller,&AbstractGameController::handleRequestForCurrentTournamentMetaData);
        connect(controller,&AbstractGameController::sendCurrentTournamentId,
                modelsContext,&AbstractModelsContext::assembleTournamentMetaDataFromId);
        /*
         * Setup request transmitting multithrow playerscores
         */
        connect(applicationInterface,&AbstractApplicationInterface::requestFTPScores,
                controller,&AbstractGameController::handleRequestFTPPlayerScores);
        connect(controller,&AbstractGameController::requestFTPScores,
                modelsContext,&AbstractModelsContext::handleRequestFTPScores);
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
                modelsContext,&AbstractModelsContext::handleResetTournament);
        connect(modelsContext,&AbstractModelsContext::tournamentResetSuccess,
                controller,&AbstractGameController::handleTournamentResetSuccess);
        /*
         * Add point
         */
        connect(applicationInterface,&AbstractApplicationInterface::requestControllerState,
                controller,&AbstractGameController::handleRequestFromUI);
        connect(applicationInterface,&AbstractApplicationInterface::sendPoint,
                controller,&AbstractGameController::handleAndProcessUserInput);
        connect(controller,&AbstractGameController::requestAddScore,
                modelsContext,&AbstractModelsContext::handleAddScore);
        connect(modelsContext,&AbstractModelsContext::scoreAddedToDataContext,
                controller,&AbstractGameController::handleScoreAddedToDataContext);
        /*
         * Undo/redo
         */
        connect(applicationInterface,&AbstractApplicationInterface::requestUndo,
                controller,&AbstractGameController::undoTurn);
        connect(applicationInterface,&AbstractApplicationInterface::requestRedo,
                controller,&AbstractGameController::redoTurn);
        connect(controller,&AbstractGameController::requestSetModelHint,
                modelsContext,&AbstractModelsContext::handleRequestSetScoreHint);
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
