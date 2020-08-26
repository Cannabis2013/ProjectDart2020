#ifndef FIVEHUNDREDANDONEGAME_H
#define FIVEHUNDREDANDONEGAME_H

#include "gamemodelscontext.h"
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

class LocalFirstToPost :public AbstractGameController
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
        Idle = 0x10,
        GameBusy = 0x11, // Game is idle but in progress
        Stopped = 0x12, // Game is stopped and no longer accepts input
        AwaitsInput = 0x13, // This should indicate that the gamecontroller is in a state where it awaits new player input
        Running = 0x14,
        WinnerDeclared = 0x15,
        NotInitialized = 0x16, // Controller is not initialized with tournament and, if necessary, appropriate indexes
        Initialized = 0x17,
        Inconsistency = 0x18,
        UndoState = 0x1F,
        RedoState = 0x20,
        AddScoreState = 0x21,
        UpdateContextState = 0x22,
        resetState = 0x40
    };
    enum ControllerResponse{
        isStopped = 0x12,
        ScoreTransmit = 0x27,
        ScoreRemove = 0x28,
        InconsistencyDetected = 0x29,
        isInitializedAndAwaitsInput = 0x2D,
        isInitializedAndReady = 0x45,
        DataProvidedSuccess =0x3D,
        WinnerFound = 0x3E
    };
    enum ControllerRequest{
        RequestBasicValues = 0x30,
        RequestIndexValues = 0x31,
        RequestPlayerScores = 0x3A,
        RequestStorePoint = 0x32,
        RequestUpdateModelState,
        RequestAddRound = 0x33,
        RequestAddSet = 0x34,
        RequestSetModelHint = 0x3C,
        RequestResetTournament = 0x3B
    };
    enum KeyMappings{
        SingleModifer = 0x2A,
        DoubleModifier = 0x2B,
        TrippleModifier = 0x2C
    };
    enum ContextCodes{
        DataContext = 0x35,
        ControllerContext = 0x36,
        ApplicationContext = 0x37
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

    void restartGame() override;
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
private:
    /* Private types
     *
     * Pointdomain refers to the interval between 180 and 'targetpoint'
     * CriticalDomain refers to points below or equal 180 but greater than zero
     * TargetDomain only consists of the number zero and is regarded as the target that defines the winner
     * Points not belonging to the above domains is not in the domain at all
     */
    enum InputPointDomain {InvalidDomain = 0x02};
    enum AggregatedSumDomains {PointDomain = 0x04,CriticalDomain = 0x06, OutsideDomain = 0x08, TargetDomain = 0xa};
    /*
     * Notify UI about controller state, current round index, undo/redo possibility and current user
     */
    void sendCurrentTurnValues();
    QString currentActiveUser()  ;
    QUuid currentActivePlayerID();
    int currentRoundIndex()  {return _roundIndex;}
    int currentPlayerIndex()  {return _setIndex;}
    int currentSetIndex() {return _setIndex;}
    int currentThrowIndex()   {return _throwIndex;}
    QUuid currentTournamentID() {return _currentTournament;}
    int status() {return _currentStatus;}
    int lastPlayerIndex()  {return _assignedPlayerTupples.count() - 1;}
    int playerIndex()   {return _setIndex;}
    QString determinedWinnerName(){return _winner;}
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
    int validateInput(const int &currentScore);
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
    void incrementTurnIndexes();
    /*
     * Get/set current player score
     */
    int playerScore(const int &index);
    void setPlayerScore(const int &index, const int &newScore);
    void setPlayerScore(const QUuid &playerID, const int &newScore);
    /*
     * Get playername from ID
     */
    QString getPlayerNameFromID(const QUuid &playerID);
    /*
     * Update playertubbles
     */
    PlayerTubbles setPlayerTubblesFromPairs(PlayerPairs pairs, const int &initialThirdValue);
    void updatePlayerTubbles(const QList<int> &scores);
    // Generate throwsuggestions
    IPointLogisticInterface<QString> *_pointLogisticInterface;
    /*
     * Controller index values
     */
    int _roundIndex = 0;
    int _setIndex = 0; // Defines player index
    int _throwIndex = 0; // Index of throw
    int _totalTurns = 0;
    int _turnIndex = 0;

    int _numberOfThrows = 3;

    const int defaultKeyPoint = 501;
    int criticalLimit = 180;

    int bullsEye = 50;

    bool _isOff;

    int _keyPoint = 0;
    QUuid _currentTournament = QUuid();
    QString _winner;
    bool _isActive = false;

    int _currentStatus;

    PlayerTubbles _assignedPlayerTupples;
};

#endif // FIVEHUNDREDANDONEGAME_H
