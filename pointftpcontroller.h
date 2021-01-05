#ifndef FIVEHUNDREDANDONEGAME_H
#define FIVEHUNDREDANDONEGAME_H

#include "ipointlogisticinterface.h"

#include "abstractgamecontroller.h"

#include <QVariantList>

#include <quuid.h>
#include <qlist.h>

#include <qthread.h>

#define GAME_IS_NOT_IN_PROGRESS "Game is not in progress"
#define GAME_WINNER_ANNOUNCEMENT(x) QString("Winner with ID: %! is declared winner").arg(x);
#define INVALID_DOMAIN "Input is not within domain";
#define UNABLE_TO_ALTER_TURN "Unable to alter turn index";

#include <iostream>

using namespace std;

class PointFTPController :public AbstractGameController
{
    Q_OBJECT
public:
    // Public types
    enum ModelDisplayHint{
        HiddenHint = 0x9,
        DisplayHint = 0xA,
        allHints = 0xB
    };
    enum ControllerState {
        GameBusy = 0x11, // Game is idle but in progress
        Stopped = 0x12, // Game is stopped and no longer accepts input
        AwaitsInput = 0x13, // This should indicate that the gamecontroller is in a state where it awaits new player input
        WinnerDeclared = 0x15,
        NotInitialized = 0x16, // Controller is not initialized with tournament and, if necessary, appropriate indexes
        Initialized = 0x17,
        UndoState = 0x1F,
        RedoState = 0x20,
        AddScoreState = 0x21,
        UpdateContextState = 0x22,
        resetState = 0x29
    };
    enum ControllerResponse{
        isStopped = 0x3A,
        ScoreTransmit = 0x27,
        ScoreRemove = 0x28,
        controllerInitializedAndAwaitsInput = 0x2D,
        controllerInitializedAndReady = 0x45,
        WinnerFound = 0x3E,
        isProcessingUserInput,
        transmitInitialScore = 0x29,
    };
    enum KeyMappings{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C,
        BullModifier,
        BullsEyeModifier
    };
    /*
     * Point suggestion section
     */
    IPointLogisticInterface<QString> *pointLogisticInterface() const;
    AbstractGameController *setPointLogisticInterface(IPointLogisticInterface<QString> *pointLogisticInterface);

    /*
     * Start/stop game progress
     */
    void start() override;
    void stop() override;

    QUuid undoTurn() override;
    QUuid redoTurn() override;
    /*
     * Controller starts initializing
     *  - Request tournament id from index provided by calling context
     *  - Request basic values
     *  - Request controller indexes
     *  - Request current playerscores
     */
    /*
     * Handle status request from UI
     */
    void handleRequestFromUI() override;
    /*
     * Handle and Evaluate input from user
     */
    void handleAndProcessUserInput(const int &point, const int &modifierKeyCode) override;
    void handleRequestForCurrentTournamentMetaData() override;
    void handleRequestForPlayerScores() override;
    void recieveTournamentDetails(const QUuid &tournament, const QString &winner,
                                  const int &keyPoint,
                                  const int &terminalKeyCode,
                                  const int &numberOfThrows,
                                  const PlayerPairs &assignedPlayerPairs) override;
    void recieveTournamentIndexes(const int &roundIndex,
                                  const int &setIndex,
                                  const int &throwIndex,
                                  const int &turnIndex,
                                  const int &totalTurns,
                                  const QList<int> &playerScores) override;

    void handleScoreAddedToDataContext(const QUuid &playerID,
                                              const int &point,
                                              const int &score) override;
    void handleDataContextUpdated() override;
    void handleScoreHintUpdated(const QUuid &playerID,
                                       const int &point,
                                       const int &score) override;
    /*
     * Reinitialize controller
     *  - Set controller back to its original state
     */
    void handleResetTournament() override;
    void handleTournamentResetSuccess() override;

private:
    /* Private types
     *
     * Pointdomain refers to the interval between 180 and 'targetpoint'
     * CriticalDomain refers to points below or equal 180 but greater than zero
     * TargetDomain only consists of the number zero and is regarded as the target that defines the winner
     * Points not belonging to the above domains is not in the domain at all
     */
    enum PointDomains {InvalidDomain = 0x02,PointDomain = 0x04,CriticalDomain = 0x06, OutsideDomain = 0x08, TargetDomain = 0xa};
    /*
     * Notify UI about controller state, current round index, undo/redo possibility and current user
     */
    void sendCurrentTurnValues();
    QString currentActiveUser()  ;
    QUuid currentActivePlayerID();
    int currentRoundIndex()  {return _roundIndex;}
    int currentPlayerIndex()  {return _setIndex;}
    int currentSetIndex() {return _setIndex;}
    int currentThrowIndex();
    int numberOfThrows() const;
    void setNumberOfThrows(int numberOfThrows);
    QUuid currentTournamentID() {return _currentTournament;}
    int status() {return _currentStatus;}
    void setCurrentStatus(int currentStatus);
    int lastPlayerIndex();
    int playerIndex();
    QString determinedWinnerName();
    /*
     * Undo/return turn
     *  - Set indexes according to the action invoked
     */
    bool canUndoTurn() ;
    bool canRedoTurn() ;
    /*
     * terminate condition
     *  - Get keycode that that terminates
     */
    int terminateConditionModifier() const;
    /*
     * Activity check
     */
    bool isActive()
    {
        return _isActive;
    }
    /*
     * Consistency check
     *  - Check if assigned tournament players is consistent with playercontext
     */
    void consistencyCheck();
    // Post validation : Validate player score after updating datacontext
    int validateCurrentState(const int &currentScore);
    /* Pre validation :
     *  - Validate input domain
     *  - Validate projected player score before updating datacontext
     */
    int validateInput(const int &currentScore, const int &modifierKeyCode, const int &userInput);
    /*
     * Update datacontext
     */
    void addPoint(const int &point, const int &score);
    /*
     * Set controller state according to datacontext
     */
    /*
     * Index manipulating methods
     */
    int currentTurnIndex();
    bool isIndexOffset();
    void nextTurn();
    void declareWinner();
    void incrementTurnIndex();
    void incrementRoundIndex();
    void incrementSetIndex();
    void resetSetIndex();
    void incrementThrowIndex();
    void resetThrowIndex();
    bool checkForEndOfSet();
    /*
     * Get/set current player score
     */
    int playerScore(const int &index);
    void setPlayerScore(const int &index, const int &newScore);
    void setPlayerScore(const QUuid &playerID, const int &newScore);
    int playerCount(){return _assignedPlayerTupples.count();}
    /*
     * Get playername from ID
     */
    QString getPlayerNameFromID(const QUuid &playerID);
    QString playerNameFromIndex(const int &index);
    /*
     * Update playertubbles
     */
    PlayerTubbles setPlayerTubblesFromPairs(PlayerPairs pairs, const int &initialThirdValue);
    void updatePlayerTubbles(const QList<int> &scores);
    // Generate throwsuggestions
    IPointLogisticInterface<QString> *_pointLogisticInterface;
    /*
     * Private getter methods
     */
    int keyPoint() const;
    /*
     * Controller index values
     */
    int _roundIndex = 0;
    int _setIndex = 0; // Equivalent to playerindex
    int _throwIndex = 0; // Index of throw
    int _totalTurns = 0;
    int _turnIndex = 0;

    int _numberOfThrows = 3;

    const int defaultKeyPoint = 501;
    const int criticalLimit = 180;

    const int bullsEye = 50;

    bool _isOff;

    int _keyPoint = defaultKeyPoint;
    QUuid _currentTournament = QUuid();
    QString _winner;
    bool _isActive = false;
    /*
     * Status member variable
     */
    int _currentStatus = ControllerState::NotInitialized;

    PlayerTubbles _assignedPlayerTupples;
};



#endif // FIVEHUNDREDANDONEGAME_H
