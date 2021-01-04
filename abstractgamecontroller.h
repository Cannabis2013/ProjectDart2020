#ifndef ABSTRACTGAMECONTROLLER_H
#define ABSTRACTGAMECONTROLLER_H

#include <QObject>
#include <quuid.h>
#include <QVariantList>
#include "iresponseinterface.h"


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

class AbstractGameController : public QObject,
        public IResponseInterface<QVariantList>
{
    Q_OBJECT
public slots:
    /*
     * Start/stop game
     */
    virtual void start() = 0;
    virtual void stop() = 0 ;
    /*
     * Recieve and evaluate UI input
     */
    virtual void handleAndProcessUserInput(const int &point, const int &modifierKeyCode) = 0;
    /*
     * Handle requests from UI
     */
    virtual void handleRequestFromUI() = 0;
    /*
     * Undo/redo turn
     */
    virtual QUuid undoTurn() = 0;
    virtual QUuid redoTurn() = 0;

    virtual void handleRequestForCurrentTournamentMetaData() = 0;
    virtual void handleRequestForPlayerScores() = 0;
    virtual void recieveTournamentDetails(const QUuid &tournament,
                                          const QString &winner,
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
    virtual void handleScoreAddedToDataContext(const QUuid &playerID,
                                                      const int &point,
                                                      const int &score) = 0;
    virtual void handleDataContextUpdated() = 0;
    virtual void handleScoreHintUpdated(const QUuid &playerID, const int &point,const int &score) = 0;
    virtual void handleTournamentResetSuccess() = 0;
    virtual void handleResetTournament() = 0;

signals:
    void transmitResponse(const int &status, const QVariantList &args) override;
    void requestTournamentMetaData(const QUuid &tournament);
    void sendAssignedTournamentPlayers(const QUuid &tournament, const PlayerPairs &assignedPlayerPairs);
    void requestTournamentIndexes(const QUuid &tournament);
    void requestAddScore(const QUuid &tournamentID,
                   const QUuid &playerID,
                   const QList<int> &dataValues,
                   const bool &isWinnerDetermined);
    void winnerDetermined(const QUuid &tournament, const QUuid &player);
    void requestUpdateContext(const QUuid &tournamentID,
                              const int &roundIndex,
                              const int &setIndex);
    void requestSetModelHint(const QUuid &tournament,
                             const QUuid &player,
                             const int &roundIndex,
                             const int &throwIndex,
                             const int &hint);
    void requestResetTournament(const QUuid &tournament);
};

#endif // ABSTRACTGAMECONTROLLER_H
