#ifndef ABSTRACTGAMECONTROLLER_H
#define ABSTRACTGAMECONTROLLER_H

#include <QObject>
#include <icontroller.h>
#include <quuid.h>
#include "istatusinterface.h"
#include <QVariantList>

typedef IController<QUuid,QString> DefaultControllerInterface;

class AbstractGameController : public QObject,
        public DefaultControllerInterface,
        public IStatusInterface<QVariantList>
{
    Q_OBJECT
public:
    /*
     * Public types
     */

public slots:
    virtual void handleInput(const int &point) = 0;
    virtual void processInput(const int &point, const int &score) = 0;
    virtual int start() = 0;
    virtual int stop() = 0 ;
    virtual void initializeController(const QUuid &tournament,const int &keyPoint, const int &numberOfThrows, QList<QUuid> assignedPlayers) = 0;
    virtual void initializeIndexes(const int &roundIndex, const int &setIndex, const int &throwIndex, const int &turnIndex, const int &totalTurns) = 0;
    virtual void handleCurrentTournamentRequest() = 0;
    virtual void handleReplyFromContext(const int &status, const QVariantList &args) = 0;
    virtual void handleStatusRequest() = 0;
signals:
    void sendPoint(const QUuid &tournamentID,
                   const QUuid &playerID,
                   const int &round,
                   const int &setIndex,
                   const int &throwIndex,
                   const int &point,
                   const int &score);
    void addRound(const QUuid &tournament, const int &index);
    void addSet(const QUuid &tournament, const int &roundIndex,const int &index);
    void sendCurrentIndexes(const QUuid &tournament, const int &roundIndex, const int &setIndex);
    void sendStatus(const int &status, const QVariantList &args) override;
    void stateChanged();
    void sendCurrentTournament(const QUuid &tournament);
    void requestInitialIndexes(const QUuid &tournament,const QList<QUuid> *assignedPlayers);
    void requestContextStatusUpdate(const QUuid &player);
    void requestScoreCalculation(const QUuid &tournament,const QUuid &player, const int &point);

};

#endif // ABSTRACTGAMECONTROLLER_H
