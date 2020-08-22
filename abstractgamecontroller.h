#ifndef ABSTRACTGAMECONTROLLER_H
#define ABSTRACTGAMECONTROLLER_H

#include <QObject>
#include <quuid.h>
#include "iresponseinterface.h"
#include <QVariantList>


typedef QList<QPair<QUuid,QString>> PlayerPairs;

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

    virtual void restartGame() = 0;

    virtual void handleCurrentTournamentRequest() = 0;
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
    virtual void confirmScoreRecieved(const QUuid &playerID, const QUuid &score) = 0;

signals:
    void transmitResponse(const int &status, const QVariantList &args);
    void sendCurrentTournament(const QUuid &tournament);
    void requestTournamentIndexes(const QUuid &tournament);
    void sendScore(const QUuid &tournamentID,
                   const QUuid &playerID,
                   const int &roundIndex,
                   const int &setIndex,
                   const int &throwIndex,
                   const int &point,
                   const int &score);
    void requestUpdateContext(const QUuid &tournamentID,
                              const QUuid &playerID,
                              const int &roundIndex,
                              const int &setIndex);
};

#endif // ABSTRACTGAMECONTROLLER_H
