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
public:
    DefaultDataInterface *tournamentModelContext(){
        return _tournamentModelContext;
    }
    void setTournamentModelContext(DefaultDataInterface *context)
    {
        _tournamentModelContext = context;
    }
    PlayerContextInterface *playerModelContext() const
    {
        return _playerModelContext;
    }
    void setPlayerModelContext(PlayerContextInterface *playerModelContext)
    {
        _playerModelContext = playerModelContext;
    }
public slots:
    virtual void createTournament(const QString &title,
                                  const int &numberOfThrows,
                                  const int &gameMode,
                                  const int &keyPoint,
                                  const QVariantList &playerIndexes) = 0;
    virtual void createPlayer(const QString &userName, const QString &mail) = 0;
    virtual void updateDataContext(const QUuid &tournament, const QUuid &player,const int &roundIndex, const int &setIndex) = 0;
    virtual void addScore(const QUuid &tournament,
                          const QString &userName,
                          const int &roundIndex,
                          const int &setIndex,
                          const int &throwIndex,
                          const int &point,
                          const int &score) = 0;
    virtual void handleSendPlayerScoresRequest(const QUuid &tournament) = 0;
    virtual void sendRequestedTournaments() = 0;
    virtual void handleSetCurrentTournament(const int &index) = 0;
    virtual void handleInitialIndexesRequest(const QUuid &tournament, const QStringList &assignedPlayers) = 0;
    virtual void handleSendPlayerDetailsRequest() = 0;
    virtual void handleControllerStatusRequest(const QUuid &playerID) = 0;
    virtual void handleScoreCalculationRequest(const QUuid &tournament, const QString &userName, const int &point) = 0;
    virtual void setScoreHint(const QUuid &tournament, const QString &userName, const int &roundIndex, const int &throwIndex, const int &hint) = 0;

signals:
    void sendContextStatus(const int &status, const QVariantList &args);
    void sendGameModes(const QStringList &gameModes);
    void stateChanged(const int &status);
    void sendPlayerDetail(const QString &userName, const QString &mailAdress);
    void sendPlayerScore(const QString &userName, const int &score);
    void sendCalculatedScore(const int &point, const int &score);
    void sendInitialControllerValues(const QUuid &tournamentID,
                                     const int &keyPoint,
                                     const int &numberOfThrows,
                                     const QStringList &players);
    void sendAssignedPlayerName(const QString &playerName);
    void sendCurrentTournamentKeyPoint(const int &point);
    void sendStatus(const int &status, const QVariantList &args);
    void sendTournament(const QString &title,
                        const int &numberOfThrows,
                        const int &gameMode,
                        const int &keyPoint,
                        const int &playersCount);
    void sendInitialControllerIndexes(const int &roundIndex,
                                      const int &setIndex,
                                      const int &throwIndex,
                                      const int &turnIndex,
                                      const int &totalTurns);

private:
    DefaultDataInterface *_tournamentModelContext;
    PlayerContextInterface *_playerModelContext;

};

#endif // ABSTRACTDATACONTEXT_H

