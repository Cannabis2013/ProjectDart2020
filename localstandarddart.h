#ifndef FIVEHUNDREDANDONEGAME_H
#define FIVEHUNDREDANDONEGAME_H

#include "idatacontext.h"
#include "igamecontroller.h"
#include "gamemodelscontext.h"
#include "ipointlogisticmanager.h"

#include <quuid.h>
#include <qlist.h>

#define GAME_IS_NOT_IN_PROGRESS "Game is not in progress"
#define GAME_WINNER_ANNOUNCEMENT(x) QString("Winner with ID: %! is declared winner").arg(x);

typedef IDataContext<QUuid,QList<QUuid>,QString> DefaultDataInterface;
typedef IGameController<QUuid,QString,DefaultDataInterface,IPointLogisticManager<QString>> DefaultControllerInterface;

class LocalStandardDart : public DefaultControllerInterface
{
public:
    LocalStandardDart();

    // IGameController interface

    QUuid start() override;
    void stop() override;
    int processInput(const int &point) override;

    QString playerMessage() const override;

    QString calculateThrowSuggestion() const override;

    QUuid currentActivePlayer() const override;

    int currentRoundIndex() const override;
    int currentPlayerIndex() const override;
    int currentLegIndex() const override;

    QUuid currentTournament() const override;

    int status() const override;

    int lastPlayerIndex() const override;
    int playerIndex() const override;

    QUuid determinedWinner() const override;

    QUuid undoTurn() override;
    QUuid redoTurn() override;

    void setDataContext(DefaultDataInterface *dataContext) override;
    DefaultDataInterface *dataContext() override;
private:
    // Pointdomain refers to the interval between 180 and 'targetpoint'
    // CriticalDomain refers to points below or equal 180 but greater than zero
    // TargetDomain only consists of the number zero and is regarded as the target that defines the winner
    // Points not belonging to the above domains is not in the domain at all
    enum InputState {PointDomain = 0x04,CriticalDomain = 0x06, OutsideDomain = 0x08, TargetDomain = 0xa};
    // Post validation : Validate player score after updating datacontext
    InputState validateCurrentState();
    // Pre validation : Validate projected player score before updating datacontext
    InputState validateInput(const int &pointValue);

    enum GameStatus {Idle = 0x20,Running = 0x22, WinnerDeclared = 0x24, notRunning = Idle | WinnerDeclared};

    QUuid addPoint(const int &point);

    int currentTurnIndex() const;

    bool isIndexOffset();

    void nextTurn();

    int sum(const int &pointValue);
    int sum(const QUuid &player);
    int sum();

    void declareWinner();

    void incrementTurnIndexes();

    QList<const QUuid> _assignedPlayers;

    // Gamestate variables
    int _playerIndex = 0; // Equal to set index
    int _roundIndex = 0;
    int _legIndex = 0;
    int _totalTurns = 0;
    int _turnIndex = 0;

    int _numberOfLegs = 3;

    int criticalLimit = 180;

    bool _isOff;

    const int _keyPoint = 0;
    QUuid _tournament;
    QUuid _winner;
    GameStatus _currentStatus = GameStatus::Idle;
    bool _isActive = false;

    // Localdata context related
    DefaultDataInterface *_dataContext;
};

#endif // FIVEHUNDREDANDONEGAME_H


