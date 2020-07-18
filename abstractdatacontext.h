#ifndef ABSTRACTDATACONTEXT_H
#define ABSTRACTDATACONTEXT_H

#include <qobject.h>

#include "idatacontext.h"
#include "modelbuildercollection.h"

#include "iplayerbuildercontext.h"
#include "iplayermodel.h"

#include "istatusinterface.h"
#include "iplayercontext.h"

typedef IPlayerModel<QUuid,QString> DefaultPlayerInterface;
typedef IPlayerBuilderParameters<QString> DefaultParameters;
typedef IDataModelBuilder<DefaultPlayerInterface,DefaultParameters,IPlayerBuilderConfiguration> DefaultPlayerBuilder;
typedef IPlayerContext<QUuid,QList<QUuid>,QString,DefaultPlayerBuilder> PlayerContextInterface;
typedef IDataContext<QUuid,QList<QUuid>,QString,ITournamentBuilder> DefaultDataInterface;

class AbstractDataContext : public QObject,
        public IStatusInterface<QVariantList>
{
    Q_OBJECT
    enum Status{DataContextReady, DataContextBusy, DataContextFailedToUpdate};
public slots:
    virtual void appendRound(const QUuid &tournament, const int &index) = 0;
    virtual void appendSet(const QUuid &tournament, const int &roundIndex, const int &setIndex) = 0;
    virtual void addScore(const QUuid &tournament,
                           const QUuid &player,
                           const int &roundIndex,
                           const int &setIndex,
                          const int &legIndex,
                          const int &point) = 0;

    PlayerContextInterface *playerModelContext() const
    {
        return _playerModelContext;
    }
    void setPlayerModelContext(PlayerContextInterface *playerModelContext)
    {
        _playerModelContext = playerModelContext;
    }

    virtual void sendPlayerScores(const QUuid &tournament) = 0;

    DefaultDataInterface *tournamentModelContext(){
        return _tournamentModelContext;
    }
    void setTournamentModelContext(DefaultDataInterface *context)
    {
        _tournamentModelContext = context;
    }
signals:
    void stateChanged(const int &status);

    void sendPlayerScore(const QString &playerName, const int &score);
    void sendInitialControllerValues(const QUuid &tournamentID,
                                     const int &keyPoint,
                                     const int &numberOfThrows,
                                     QList<QUuid> players);
    void sendAssignedPlayerName(const QString &playerName);
    void sendCurrentTournamentKeyPoint(const int &point);

    void sendStatus(const int &status, const QVariantList &args);
private:
    DefaultDataInterface *_tournamentModelContext;
    PlayerContextInterface *_playerModelContext;

};

#endif // ABSTRACTDATACONTEXT_H




