#ifndef ABSTRACTMODELSCONTEXT_H
#define ABSTRACTMODELSCONTEXT_H
#include <QFuture>
#include <qobject.h>
#include "PlayerModelsContext/playermodelscontext.h"
class AbstractModelsContext : public QObject
{
    Q_OBJECT
public:
    virtual ~AbstractModelsContext() = default;
public slots:
    virtual void addTournament(const QByteArray& json) = 0;
    virtual void deleteTournaments(const QVector<int>& indexes) = 0;
    virtual void getTournaments() = 0;
    virtual QFuture<bool> resetTournament(const QUuid &tournament) = 0;
    virtual void setTournamentWinner(const QByteArray& json) = 0;
    virtual void setPlayerModelsContext(PlayerModelsContext *context) = 0;
signals:
    void sendTournaments(const QByteArray& json);
    void tournamentResetSuccess();
    void tournamentResetFailed();
    void requestAssembleTournament(const QUuid &tournament);
    void tournamentsDeletedStatus(const bool &status);
};
#endif // ABSTRACTMODELSCONTEXT_H
