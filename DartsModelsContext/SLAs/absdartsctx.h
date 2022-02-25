#ifndef ABSDARTSCTX_H
#define ABSDARTSCTX_H
#include <qobject.h>
#include "dartsmodelsservices.h"
class IDartsIndex;
class IDartsInput;
class IPlayer;
class IDartsTournament;
class AbsPlaCtx;
class AbsDartsCtx : public QObject
{
    Q_OBJECT
public:
    virtual ~AbsDartsCtx() = default;
    Q_INVOKABLE virtual QByteArray tournaments() = 0;
    Q_INVOKABLE virtual QByteArray tournament(const int &index) const = 0;
    Q_INVOKABLE virtual QByteArray tournament(const QString &id) const = 0;
    Q_INVOKABLE virtual bool isConsistent(const QUuid &tournamentId) const = 0;
    Q_INVOKABLE virtual bool tryRepair(const QUuid &tournamentId) = 0;
    Q_INVOKABLE virtual bool deleteTournaments(const QVector<int> &indexes) = 0;
    Q_INVOKABLE virtual bool addTournament(const QByteArray& json, const QVector<int> &playerIndexes) = 0;
    Q_INVOKABLE virtual QByteArray createDartsMetaData(const QUuid& tournament) = 0;
    Q_INVOKABLE virtual QByteArray inputs(const QUuid &tournamentId) const = 0;
    virtual void setTournamentWinner(const QUuid &tournamentId, const QString &name) = 0;
    virtual QByteArray tournament(const QUuid &id) const = 0;
    virtual bool resetTournament(const QUuid &tournamentId) = 0;
    virtual QByteArray input(const QUuid &tournament, const QString &name, const QByteArray &indexByteArray) const = 0;
    virtual bool addInput(const QUuid &tournamentId, const QByteArray &byteArray) = 0;
    virtual bool hideInput(QUuid tournament, QString name, const QByteArray &indexByteArray) = 0;
    virtual bool revealInput(QUuid tournament, QString name, const QByteArray &indexByteArray) = 0;
    virtual bool updateTournamentIndex(QUuid tournament, const QByteArray &indexByteArray) = 0;
};
#endif // ABSDARTSCTX_H
