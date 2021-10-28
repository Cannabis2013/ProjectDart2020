#ifndef ABSTRACTGAMECONTROLLER_H
#define ABSTRACTGAMECONTROLLER_H
#include <QObject>
#include <quuid.h>
class AbstractGameController : public QObject
{
    Q_OBJECT
public slots:
    virtual void handleUserInput(const QByteArray& json) = 0;
    virtual void createJsonResponse() = 0;
    virtual void undoTurn() = 0;
    virtual void redoTurn() = 0;
    virtual void createIndexJson() = 0;
    virtual void sendTournamentId() = 0;
    virtual void reset() = 0;
    virtual void beginInitialize() = 0;
    virtual void requestStatus() = 0;
signals:
    void ready();
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
