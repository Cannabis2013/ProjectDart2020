#ifndef ABSDARTSCTRL_H
#define ABSDARTSCTRL_H
#include "ctrlslas.h"
#include <qobject.h>
class AbsDartsCtx;
class AbsDartsCtrl : public QObject, public CtrlSLAs
{
    Q_OBJECT
public:
    Q_INVOKABLE virtual QString tournamentId() const = 0;
    Q_INVOKABLE virtual QByteArray undoTurn() = 0;
    Q_INVOKABLE virtual QByteArray redoTurn() = 0;
    Q_INVOKABLE virtual QByteArray addInput(const QByteArray& json) = 0;
    Q_INVOKABLE virtual bool reset() = 0;
    Q_INVOKABLE virtual int status() const = 0;
    Q_INVOKABLE virtual QByteArray getWinnerJson() const = 0;
    Q_INVOKABLE virtual int initialize(const QUuid &tournamentId) = 0;
    Q_INVOKABLE virtual QByteArray getPlayerScores() const = 0;
    Q_INVOKABLE virtual QByteArray getTurnValues() const = 0;
    void setModelsContext(AbsDartsCtx *context) {_modelsContext = context;}
    AbsDartsCtx *mdsCtx() {return _modelsContext;}
signals:
    void ready();
    void resetSucces();
    void sendCurrentTournamentId(const QUuid &tournament);
    void winnerDetermined(const QByteArray& json);
    void controllerIsNotInitialized();
    void winnerDeclared(const QByteArray& json);
    void controllerIsStopped();
    void initialized();
    void controllerAwaitsInput();
    void updateTournamentIndex(const QByteArray &json);
    void requestDartsTournamentDetails(const QUuid& tournamentId);
    void updatePlayerScore(const QByteArray& json);
    void sendDartsScores(const QByteArray& json);
    void sendOrderedInputs(const QByteArray &json);
private:
    AbsDartsCtx *_modelsContext = nullptr;
};
#endif
