#ifndef IDARTSCTRL_H
#define IDARTSCTRL_H
#include <qobject.h>
#include "ServicesProvider/dcservices.h"
class AbsDartsCtx;
class IDartsCtrl : public QObject
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
};
#endif
