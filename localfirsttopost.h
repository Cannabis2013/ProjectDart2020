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
    enum ModelDisplayHint{HiddenHint = 0x1,DisplayHint = 0x2, allHints = 0x4};

    int start() override;
    int stop() override;

    int processInput(const int &point) override;

    QString playerMessage()  override;

    QString calculateThrowSuggestion()  override;

    QUuid currentActivePlayer()  override;

    int currentRoundIndex()  override;
    int currentPlayerIndex()  override;
    int currentSetIndex() override;
    int currentLegIndex()  override;

    QUuid currentTournamentID()  override;
    void setCurrentTournament(QUuid &tournament) override;

    int status() override;

    int lastPlayerIndex()  override;
    int playerIndex()  override;

    QUuid determinedWinner()  override;

    QUuid undoTurn() override;
    QUuid redoTurn() override;

    bool canUndoTurn() override;
    bool canRedoTurn() override;

    int score(const QUuid &player) override;

    IPointLogisticManager<QString> *pointLogisticInterface() const;
    AbstractGameController *setPointLogisticInterface(IPointLogisticManager<QString> *pointLogisticInterface);
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
     * Consistency check
     *
     * Check if assigned tournament players is consistent with playercontext
     */
    void consistencyCheck();
    // Post validation : Validate player score after updating datacontext
    int validateCurrentState();
    /* Pre validation :
     *  - Validate input domain
     *  - Validate projected player score before updating datacontext
     */
    int validateInput(const int &pointValue);
    /*
     * Update datacontext
     */
    QUuid addPoint(const int &point);
    /*
     * Update controller state and indexes according to current tournament
     */
    void initializeController(const QUuid &tournament);
    void initializeIndexes(const QUuid &tournament);
    /*
     * Set controller state according to datacontext
     */
    /*
     * Index methods
     */
    int currentTurnIndex() ;
    bool isIndexOffset();

    void nextTurn();

    int sum(const int &pointValue);
    int sum(const QUuid &player);
    int sum();

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
    QUuid _tournament = QUuid();
    QUuid _winner;
    GameStatus _currentStatus = GameStatus::GameControllerStopped;
    bool _isActive = false;

    // Localdata context related
    IPointLogisticManager<QString> *_pointLogisticInterface;
};

#endif // FIVEHUNDREDANDONEGAME_H


