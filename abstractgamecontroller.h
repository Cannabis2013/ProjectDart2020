#ifndef ABSTRACTGAMECONTROLLER_H
#define ABSTRACTGAMECONTROLLER_H

#include <QObject>
#include <quuid.h>
#include "iresponseinterface.h"
#include <QVariantList>


template<class T1, class T2, class T3>
struct Tupple
{
public:
    Tupple(T1 firstArg, T2 secondArg, T3 thirdArg)
    {
        first = firstArg;
        second = secondArg;
        third = thirdArg;
    }
    T1 first;
    T2 second;
    T3 third;
};

typedef Tupple<QUuid,QString,int> PlayerTupple;
typedef QList<PlayerTupple> PlayerTubbles;
typedef QPair<QUuid,QString> PlayerPair;
typedef QList<PlayerPair> PlayerPairs;

class AbstractGameController : public QObject
{
    Q_OBJECT
public:
    /*
     * Public types
     */

public slots:
    virtual void handleAndProcessUserInput(const int &point, const int &modifierKeyCode) = 0;
    virtual void start() = 0;
    virtual void stop() = 0 ;
    /*
     * Handle requests from datacontext
     */
    virtual void handleRequestFromUI() = 0;
    /*
     * Undo/redo turn
     */
    virtual QUuid undoTurn() = 0;
    virtual QUuid redoTurn() = 0;
    /*
     * Restart game
     */
    virtual void restartGame() = 0;

    virtual void handleRequestForCurrentTournamentMetaData() = 0;
    virtual void handleRequestForPlayerScores() = 0;
    virtual void recieveTournamentDetails(const QUuid &tournament,
                                          const int &keyPoint,
                                          const int &terminalKeyCode,
                                          const int &numberOfThrows,
                                          const PlayerPairs &assignedPlayerNames) = 0;
    virtual void recieveTournamentIndexes(const int &roundIndex,
                                          const int &setIndex,
                                          const int &throwIndex,
                                          const int &turnIndex,
                                          const int &totalTurns,
                                          const QList<int> &playerScores) = 0;
    virtual void handleConfirmScoreAddedToDataContext(const QUuid &playerID,
                                                      const int &point,
                                                      const int &score) = 0;
    virtual void handleConfirmDataContextUpdated() = 0;

signals:
    void transmitResponse(const int &status, const QVariantList &args);
    void sendCurrentTournamentForTournamentMetaData(const QUuid &tournament);
    void sendCurrentTournamentForTransmittingScorePoints(const QUuid &tournament, const PlayerPairs &assignedPlayerPairs);
    void requestTournamentIndexes(const QUuid &tournament);
    void sendScore(const QUuid &tournamentID,
                   const QUuid &playerID,
                   const int &roundIndex,
                   const int &setIndex,
                   const int &throwIndex,
                   const int &point,
                   const int &score);
    void requestUpdateContext(const QUuid &tournamentID,
                              const int &roundIndex,
                              const int &setIndex);
};

#endif // ABSTRACTGAMECONTROLLER_H
