#ifndef ABSTRACTMDSCTX_H
#define ABSTRACTMDSCTX_H
#include <QFuture>
#include <qobject.h>
#include <DartsModelsContext/TournamentModelsSLAs/abstractdartstournament.h>
#include "PlayerModelsContext/playerscontext.h"
class AbstractMdsCtx : public QObject
{
    Q_OBJECT
public:
    virtual ~AbstractMdsCtx() = default;
    Q_INVOKABLE virtual QByteArray tournaments() = 0;
    Q_INVOKABLE virtual QByteArray tournament(const int &index) const = 0;
    Q_INVOKABLE virtual QByteArray tournament(const QString &id) const = 0;
    Q_INVOKABLE virtual bool isConsistent(const QUuid &tournamentId) const = 0;
    Q_INVOKABLE virtual void tryRepair(const QUuid &tournamentId) = 0;
    Q_INVOKABLE virtual bool deleteTournaments(const QVector<int> &indexes) = 0;
    Q_INVOKABLE virtual bool addTournament(const QByteArray& json, const QVector<int> &playerIndexes) = 0;
    Q_INVOKABLE virtual bool setTournamentWinner(const QByteArray& json) = 0;
    virtual ITournament *tournament(const QUuid &id) const = 0;
    virtual QVector<IPlayerModel*> players(const QUuid &tournamentId) const = 0;
    virtual bool resetTournament(const QUuid &tournamentId) = 0;
signals:
    void tournamentResetSuccess();
    void tournamentResetFailed();
    void tournamentsDeleted();
    void repairCompleted(const bool &status, const QByteArray &json);
};
#endif // ABSTRACTMDSCTX_H
