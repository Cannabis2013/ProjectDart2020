#ifndef ABSTRACTGAMECONTROLLER_H
#define ABSTRACTGAMECONTROLLER_H

#include <QObject>
#include <icontroller.h>
#include <quuid.h>


typedef IController<QUuid,QString> DefaultControllerInterface;

class AbstractGameController : public QObject, public DefaultControllerInterface
{
    Q_OBJECT
public:
    /*
     * Public types
     */
    enum GameStatus {GameControllerIdle = 0x9,
                     GamecontrollerBusy = 0xa, // Game is idle but in progress
                     GameControllerStopped = 0xb, // Game is stopped and no longer accepts input
                     GameControllerAwaitsInput = 0xc, // This should indicate that the gamecontroller is in a state where it awaits new player input
                     GameControllerRunning = 0xd,
                     GameControllerWinnerDeclared = 0xe,
                     GameControllerNotInitialized = 0xf};

public slots:
    virtual int processInput(const int &point, const int &currentScore) = 0;

    virtual int start() = 0;
    virtual int stop() = 0 ;
    virtual void initializeController(const QUuid &tournament,const int &keyPoint, const int &numberOfThrows, QList<QUuid> assignedPlayers) = 0;
    virtual void initializeIndexes(const int &roundIndex, const int &setIndex, const int &throwIndex, const int &turnIndex, const int &totalTurns) = 0;
    virtual void handleCurrentTournamentRequest() = 0;
signals:
    void sendPoint(const QUuid &tournamentID,
                   const QUuid &playerID,
                   const int &round,
                   const int &setIndex,
                   const int &throwIndex,
                   const int &point);
    void addRoundRequest(const QUuid &tournament, const int &index);
    void addSetRequest(const QUuid &tournament, const int &roundIndex,const int &index);
    void sendStatus(const int &status);
    void stateChanged();
    void sendCurrentTournament(const QUuid &tournament);

};

#endif // ABSTRACTGAMECONTROLLER_H
