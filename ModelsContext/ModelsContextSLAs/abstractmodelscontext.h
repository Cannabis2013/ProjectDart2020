#ifndef ABSTRACTMODELSCONTEXT_H
#define ABSTRACTMODELSCONTEXT_H
#include <QFuture>
#include <qobject.h>
#include "PlayerModelsContext/playerscontext.h"
class AbstractModelsContext : public QObject
{
    Q_OBJECT
public:
    virtual ~AbstractModelsContext() = default;
    Q_INVOKABLE virtual QByteArray tournaments() = 0;
    Q_INVOKABLE virtual QByteArray tournament(const int &index) const = 0;
    Q_INVOKABLE virtual QByteArray tournament(const QString &id) const = 0;
    Q_INVOKABLE virtual bool isConsistent(const QUuid &tournamentId) const = 0;
    Q_INVOKABLE virtual bool tryRepair(const QUuid &tournamentId) const = 0;
    virtual IModel<QUuid> *tournament(const QUuid &id) const = 0;
    virtual QVector<IModel<QUuid>*> assignedPlayers(const QUuid &tournamentId) const = 0;
    virtual QFuture<bool> resetTournament(const QUuid &tournament) = 0;
public slots:
    virtual void addTournament(const QByteArray& json, const QVector<int> &playerIndexes) = 0;
    virtual void deleteTournaments(const QVector<int>& indexes) = 0;
    virtual void setTournamentWinner(const QByteArray& json) = 0;
signals:
    void sendTournaments(const QByteArray& json);
    void tournamentResetSuccess();
    void tournamentResetFailed();
    void requestAssembleTournament(const QUuid &tournament);
    void tournamentsDeleted();
};
#endif // ABSTRACTMODELSCONTEXT_H
