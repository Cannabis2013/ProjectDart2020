#ifndef ABSTRACTGAMECONTROLLER_H
#define ABSTRACTGAMECONTROLLER_H

#include <QObject>
#include <icontroller.h>
#include <quuid.h>
#include "iresponseinterface.h"
#include <QVariantList>

typedef IController<QUuid,QString> DefaultControllerInterface;

class AbstractGameController : public QObject,
        public DefaultControllerInterface,
        public IResponseInterface<QVariantList>
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

    virtual void setCurrentTournament(const int &index) = 0;

    /*
     * The following slot is invoked when datacontext needs to know the current tournament id
     */
    virtual void handleCurrentTournamentRequest() = 0;
    /*
     * Handle request and response from different contexts
     */

    virtual void handleRequestFromContext(const int &context, const int &request, const QVariantList &args) override = 0;
    virtual void handleResponseFromContext(const int &context, const int &response, const QVariantList &args) override = 0;
    /*
     * Handle requests from datacontext
     */
    virtual void handleControllerStateRequest() = 0;
    /*
     * Undo/redo turn
     */
    virtual QUuid undoTurn() = 0;
    virtual QUuid redoTurn() = 0;

signals:
    void sendPoint(const QUuid &tournamentID,
                   const QString &playerName,
                   const int &round,
                   const int &setIndex,
                   const int &throwIndex,
                   const int &point,
                   const int &score);
    void addRound(const QUuid &tournament, const int &index);
    void addSet(const QUuid &tournament, const int &roundIndex,const int &index);
    void sendCurrentIndexes(const QUuid &tournament, const QUuid &player, const int &roundIndex, const int &setIndex);
    void transmitResponse(const int &status, const QVariantList &args);
    void stateChanged();
    void requestInitialIndexes(const QUuid &tournament,const QStringList &assignedPlayers);
    void requestContextStatusUpdate(const QUuid &player);
    void requestScoresFromDataContext(const QUuid &tournament,const QStringList &userNames);
    void requestSetScoreHint(const QUuid &tournament,
                             const QString &playerName,
                             const int &roundIndex,
                             const int &throwIndex,
                             const int &hint);
    void removeScore(const QString &playerName);

    void sendRequestToDataContext(const int &context, const int &request, const QVariantList &args);
    void sendResponseToDataContext(const int &context, const int &response, const QVariantList &args);

};

#endif // ABSTRACTGAMECONTROLLER_H
