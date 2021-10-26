#ifndef ABSTRACTGAMECONTROLLER_H
#define ABSTRACTGAMECONTROLLER_H

#include <QObject>
#include <quuid.h>

class AbstractGameController : public QObject
{
    Q_OBJECT
public slots:
    // Start/stop game
    virtual void start() = 0;
    virtual void stop() = 0 ;
    // Recieve and evaluate UI input
    virtual void handleUserInput(const QByteArray& json) = 0;
    // Handle requests from UI
    virtual void handleRequestFromUI() = 0;
    // Undo/redo turn
    virtual void undoTurn() = 0;
    virtual void redoTurn() = 0;
    virtual void handleRequestForCurrentTournamentMetaData() = 0;
    virtual void reset() = 0;
    // Set initial state
    virtual void beginInitialize() = 0;
    // Player details
    virtual void initializePlayerDetails(const QByteArray&) = 0;
    virtual void initializeWinnerDetails(const QByteArray&) = 0;
signals:
    void sendCurrentTournamentId(const QUuid &tournament);
    void winnerDetermined(const QByteArray& json);
    void requestUpdateContext(const QUuid &tournamentID,
                              const int &roundIndex,
                              const int &setIndex);
    void requestResetTournament(const QUuid &tournament);
    void requestPersistModelState();
    void controllerIsNotInitialized();
    void resetSucces();
    void winnerDeclared(const QByteArray& json);
    void controllerIsStopped();
};

#endif // ABSTRACTGAMECONTROLLER_H
