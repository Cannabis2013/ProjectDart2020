#ifndef FIVEHUNDREDANDONEGAME_H
#define FIVEHUNDREDANDONEGAME_H

#include "idatacontext.h"
#include "igamecontroller.h"
#include "gamemodelscontext.h"
#include "pointlogisticmanager.h"

#include "localdatacontext.h"

#include <quuid.h>
#include <qlist.h>

#define GAME_IS_NOT_IN_PROGRESS "Game is not in progress"
#define GAME_WINNER_ANNOUNCEMENT(x) QString("Winner with ID: %! is declared winner").arg(x);
#define INVALID_DOMAIN "Input is not within domain";
#define UNABLE_TURN "Unable to alter turn index";

typedef IGameController<QUuid,QString,DefaultDataInterface> DefaultControllerInterface;

class LocalStandardDart : public DefaultControllerInterface
{
public:
    // Public types
    enum GameStatus {Idle = 0xc,
                     Running = 0xe,
                     WinnerDeclared = 0x10,
                     notRunning = Idle | WinnerDeclared};
    LocalStandardDart();

    // IGameController interface

    QUuid start() override;
    void stop() override;
    int processInput(const int &point) override;

    QString playerMessage()  override;

    QString calculateThrowSuggestion()  override;

    QUuid currentActivePlayer()  override;

    int currentRoundIndex()  override;
    int currentPlayerIndex()  override;
    int currentSetIndex() override;
    int currentLegIndex()  override;

    QUuid currentTournament()  override;
    void setCurrentTournament(QUuid &tournament) override;

    int status() override;

    int lastPlayerIndex()  override;
    int playerIndex()  override;

    QUuid determinedWinner()  override;

    QUuid undoTurn() override;
    QUuid redoTurn() override;

    void setDataContext(DefaultDataInterface *dataContext) override;
    DefaultDataInterface *dataContext()  override;

private:
    /* Private types
     *
     * Pointdomain refers to the interval between 180 and 'targetpoint'
     * CriticalDomain refers to points below or equal 180 but greater than zero
     * TargetDomain only consists of the number zero and is regarded as the target that defines the winner
     * Points not belonging to the above domains is not in the domain at all
     */
    enum InputPointDomain {InvalidDomain = 0x02};
    enum AggregatedSumDomain {PointDomain = 0x04,CriticalDomain = 0x06, OutsideDomain = 0x08, TargetDomain = 0xa};
    // Post validation : Validate player score after updating datacontext
    int validateCurrentState();
    /* Pre validation :
     *  - Validate input domain
     *  - Validate projected player score before updating datacontext
     */
    int validateInput(const int &pointValue);

    QUuid addPoint(const int &point);

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
    int _playerIndex = 0; // Equal to set index
    int _roundIndex = 0;
    int _legIndex = 0;
    int _totalTurns = 0;
    int _turnIndex = 0;

    int _numberOfLegs = 3;

    int defaultKeyPoint = 501;
    int criticalLimit = 180;

    bool _isOff;

    int _keyPoint = 0;
    QUuid _tournament;
    QUuid _winner;
    GameStatus _currentStatus = GameStatus::Idle;
    bool _isActive = false;

    // Localdata context related
    DefaultDataInterface *_dataContext;
};

#endif // FIVEHUNDREDANDONEGAME_H


