#ifndef FIVEHUNDREDANDONEGAME_H
#define FIVEHUNDREDANDONEGAME_H

#include "gamemodelscontext.h"
#include "ipointlogisticmanager.h"

#include "abstractgamecontroller.h"

#include <QVariantList>

#include <quuid.h>
#include <qlist.h>

#define GAME_IS_NOT_IN_PROGRESS "Game is not in progress"
#define GAME_WINNER_ANNOUNCEMENT(x) QString("Winner with ID: %! is declared winner").arg(x);
#define INVALID_DOMAIN "Input is not within domain";
#define UNABLE_TO_ALTER_TURN "Unable to alter turn index";

class LocalFirstToPost :public AbstractGameController
{
    Q_OBJECT
public:
    // Public types
    enum ModelDisplayHint{HiddenHint = 0x9,DisplayHint = 0xA, allHints = 0xB};
    enum ControllerState {Idle = 0x10,
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
                     UpdateContextState = 0x22};
    enum Status{ContextBusy = 0xC,
                ContextReady = 0xD,
                ContextSuccessfullyUpdated = 0xE,
                ContextUnSuccessfullyUpdated = 0xF,
                ContextDataProvided = 0x19};
public slots:
    /*
     * Start/stop game progress
     */
    void start() override;
    void stop() override;

    QUuid undoTurn() override;
    QUuid redoTurn() override;

    /*
     * The following methods handle the initial state of the gamecontroller where it needs to set the following values:
     *  - Key values like keypoint, current tournament id, etc.
     *  - Initial indexes like turnindex, throwindex, etc.
     *  - Current usernames scores
     */
    void handleInitialValuesFromDataContext(const QUuid &tournament,
                                            const int &keyPoint,
                                            const int &numberOfThrows,
                                            const QVector<QString> &assignedUserNames) override;
    void handleIndexesFromDatacontext(const int &roundIndex,
                           const int &setIndex,
                           const int &throwIndex,
                           const int &turnIndex,
                           const int &totalTurns) override;
    void handleRequestedScoresFromDataContext(const QVector<int> &scores) override;
    /*
     * The following slot is invoked when datacontext needs to know the current tournament id
     */
    void handleCurrentTournamentRequest() override;
    /*
     * Handle reply from datacontext
     *  - This is requested everytime a transaction has taken place between this class and the datacontext
     */
    void handleReplyFromDataContext(const int &status, const QVariantList &args) override;

    void handleControllerStateRequest() override;

    /*
     * Handle and Evaluate input from user
     */
    void handleAndProcessUserInput(const int &point) override;
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
    QString playerMessage()  override;
    QString calculateThrowSuggestion(const int &score)  override;
    QString currentActiveUser()  override;
    int currentRoundIndex()  override{return _roundIndex;}
    int currentPlayerIndex()  override{return _setIndex;}
    int currentSetIndex() override{return _setIndex;}
    int currentThrowIndex()  override {return _throwIndex;}
    QUuid currentTournamentID()  override {return _currentTournament;}
    int status() override{return _currentStatus;}
    int lastPlayerIndex()  override{return _assignedUserNames.count() - 1;}
    int playerIndex()  override {return _setIndex;}
    QUuid determinedWinner()  override {return _winner;}

    bool canUndoTurn() override;
    bool canRedoTurn() override;

    IPointLogisticManager<QString> *pointLogisticInterface() const;
    AbstractGameController *setPointLogisticInterface(IPointLogisticManager<QString> *pointLogisticInterface);
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
     * Index methods
     */
    int currentTurnIndex()
    {
        return _turnIndex;
    }
    bool isIndexOffset()
    {
        return _isOff;
    }
    void nextTurn();
    void declareWinner();
    void incrementTurnIndexes();

    /*
     * Get current player score
     */

    int playerScore(const int &index);
    void setPlayerScore(const int &index, const int &newScore);


    // Gamestate variables
    int _roundIndex = 0;
    int _setIndex = 0; // Defines player index
    int _throwIndex = 0; // Index of throw
    int _totalTurns = 0;
    int _turnIndex = 0;

    int _numberOfThrows = 3;

    const int defaultKeyPoint = 501;
    int criticalLimit = 180;

    bool _isOff;

    int _keyPoint = 0;
    QUuid _currentTournament = QUuid();
    QUuid _winner;
    ControllerState _currentStatus = ControllerState::NotInitialized;
    bool _isActive = false;

    QVector<QString> _assignedUserNames;
    QVector<int> _assignedUsernamesScore;

    // Generate throw suggest message
    IPointLogisticManager<QString> *_pointLogisticInterface;
};

#endif // FIVEHUNDREDANDONEGAME_H
