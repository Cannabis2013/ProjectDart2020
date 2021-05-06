#ifndef ABSTRACTGAMECONTROLLER_H
#define ABSTRACTGAMECONTROLLER_H

#include <QObject>
#include <quuid.h>
#include "iresponseinterface.h"

class AbstractGameController : public QObject
{
    Q_OBJECT
public slots:
    virtual void initializeControllerIndexes(const QByteArray&) = 0;
    /*
     * Start/stop game
     */
    virtual void start() = 0;
    virtual void stop() = 0 ;
    /*
     * Recieve and evaluate UI input
     */
    virtual void handleAndProcessUserInput(const QByteArray& json) = 0;
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
    virtual void handleScoreAddedToDataContext(const QByteArray& json) = 0;
    virtual void handleResetTournament() = 0;
    /*
     * Set initial state
     */
    virtual void beginInitialize() = 0;
    /*
     * Handle persist model request
     */
    virtual void handleRequestPersistCurrentState() = 0;
signals:
    void sendCurrentTournamentId(const QUuid &tournament);
    void winnerDetermined(const QUuid &tournament, const QUuid &player);
    void requestUpdateContext(const QUuid &tournamentID,
                              const int &roundIndex,
                              const int &setIndex);
    void requestResetTournament(const QUuid &tournament);
    void requestPersistModelState();
    void controllerIsNotInitialized();
    void isReset();
    void winnerDeclared(const QString& jsons);
    void controllerIsStopped();
};

#endif // ABSTRACTGAMECONTROLLER_H
