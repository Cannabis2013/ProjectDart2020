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
    enum GameStatus {GameControllerIdle = 0x10,
                     GameControllerBusy = 0x11, // Game is idle but in progress
                     GameControllerStopped = 0x12, // Game is stopped and no longer accepts input
                     GameControllerAwaitsInput = 0x13, // This should indicate that the gamecontroller is in a state where it awaits new player input
                     GameControllerRunning = 0x14,
                     GameControllerWinnerDeclared = 0x15,
                     GameControllerNotInitialized = 0x16,
                     GameControllerInitialized = 0x17}; // Controller is not initialized with tournament and, if necessary, appropriate indexes
    enum Status{ContextBusy = 0xC, ContextReady = 0xD,ContextSuccessfullyUpdated = 0xE,ContextUnSuccessfullyUpdated = 0xF};

    int start() override;
    int stop() override;

    int processInput(const int &point, const int &currentScore) override;

    QString playerMessage()  override;

    QString calculateThrowSuggestion(const int &score)  override;

    QUuid currentActivePlayer()  override;

    int currentRoundIndex()  override;
    int currentPlayerIndex()  override;
    int currentSetIndex() override;
    int currentLegIndex()  override;

    QUuid currentTournamentID()  override;

    int status() override;

    int lastPlayerIndex()  override;
    int playerIndex()  override;

    QUuid determinedWinner()  override;

    QUuid undoTurn() override;
    QUuid redoTurn() override;

    bool canUndoTurn() override;
    bool canRedoTurn() override;

    IPointLogisticManager<QString> *pointLogisticInterface() const;
    AbstractGameController *setPointLogisticInterface(IPointLogisticManager<QString> *pointLogisticInterface);
public slots:
    void initializeController(const QUuid &tournament, const int &keyPoint, const int &numberOfThrows, QList<QUuid> assignedPlayers) override;
    void initializeIndexes(const int &roundIndex,
                           const int &setIndex,
                           const int &throwIndex,
                           const int &turnIndex,
                           const int &totalTurns) override;
    void handleCurrentTournamentRequest() override;

    void recieveStatus(const int &status, const QVariantList &args) override;
    void handleReplyFromContext(const int &status) override;
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
    bool isActive();
    /*
     * Consistency check
     *  - Check if assigned tournament players is consistent with playercontext
     */
    void consistencyCheck();
    // Post validation : Validate player score after updating datacontext
    int validateCurrentState(const int &score);
    /* Pre validation :
     *  - Validate input domain
     *  - Validate projected player score before updating datacontext
     */
    int validateInput(const int &pointValue, const int &currentScore);
    /*
     * Update datacontext
     */
    void addPoint(const int &point);
    /*
     * Set controller state according to datacontext
     */
    /*
     * Index methods
     */
    int currentTurnIndex() ;
    bool isIndexOffset();
    void nextTurn();
    void declareWinner();
    void incrementTurnIndexes();

    QList< QUuid> _assignedPlayers;

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
    GameStatus _currentStatus = GameStatus::GameControllerNotInitialized;
    bool _isActive = false;

    // Localdata context related
    IPointLogisticManager<QString> *_pointLogisticInterface;
};

#endif // FIVEHUNDREDANDONEGAME_H
