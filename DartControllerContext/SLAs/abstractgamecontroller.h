#ifndef ABSTRACTGAMECONTROLLER_H
#define ABSTRACTGAMECONTROLLER_H
#include <QObject>
#include <quuid.h>
#include "DartsModelsContext/SLAs/abstractdartscontext.h"
class AbstractGameController : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE virtual QString tournamentId() const = 0;
    Q_INVOKABLE virtual void undoTurn() = 0;
    Q_INVOKABLE virtual void redoTurn() = 0;
    Q_INVOKABLE virtual void handleUserInput(const QByteArray& json) = 0;
    Q_INVOKABLE virtual void reset() = 0;
    Q_INVOKABLE virtual QByteArray getTurnValuesJson() = 0;
signals:
    void ready();
    void resetSucces();
    void sendCurrentTournamentId(const QUuid &tournament);
    void winnerDetermined(const QByteArray& json);
    void controllerIsNotInitialized();
    void winnerDeclared(const QByteArray& json);
    void controllerIsStopped();
};

#endif // ABSTRACTGAMECONTROLLER_H
