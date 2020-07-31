#ifndef ABSTRACTDATACONTEXT_H
#define ABSTRACTDATACONTEXT_H

#include <qobject.h>

#include "idatacontext.h"
#include "modelbuildercollection.h"

#include "iplayerbuildercontext.h"
#include "iplayermodel.h"

#include "iresponseinterface.h"
#include "iplayercontext.h"

typedef IPlayerModel<QUuid,QString> DefaultPlayerInterface;
typedef IPlayerBuilderParameters<QString,QUuid> DefaultParameters;
typedef IDataModelBuilder<DefaultPlayerInterface,DefaultParameters,IPlayerBuilderConfiguration> DefaultPlayerBuilder;
typedef IPlayerContext<QUuid,QList<QUuid>,QString,DefaultPlayerBuilder> PlayerContextInterface;
typedef IDataContext<QUuid,QList<QUuid>,QString,ITournamentBuilder> DefaultDataInterface;

class AbstractDataContext : public QObject,
        public IResponseInterface<QVariantList>
{
    Q_OBJECT
public:
    AbstractDataContext(DefaultDataInterface *tournamentModelsContext, PlayerContextInterface *playerModelsContext):
        _tournamentModelContext(tournamentModelsContext),
        _playerModelsContext(playerModelsContext){}
    ~AbstractDataContext() = default;
    DefaultDataInterface *tournamentModelsContext(){
        return _tournamentModelContext;
    }
    void setTournamentModelContext(DefaultDataInterface *context)
    {
        _tournamentModelContext = context;
    }
    PlayerContextInterface *playerModelsContext() const
    {
        return _playerModelsContext;
    }
    void setPlayerModelsContext(PlayerContextInterface *playerModelContext)
    {
        _playerModelsContext = playerModelContext;
    }
public slots:
    virtual void handleCreateTournamentRequest(const QString &title,
                                  const int &numberOfThrows,
                                  const int &gameMode,
                                  const int &keyPoint,
                                  const QVariantList &playerIndexes) = 0;
    virtual void handleCreatePlayerRequest(const QString &playerName, const QString &mail) = 0;
    virtual void handleDeletePlayerRequest(const int &index) = 0;
    virtual void updateDataContext(const QUuid &tournament, const QUuid &player,const int &roundIndex, const int &setIndex) = 0;
    virtual void handleTournamentsRequest() = 0;
    virtual void handleSendPlayerDetailsRequest() = 0;
    virtual void deleteTournamentsFromIndexes(const QVariantList &indexes) = 0;

    virtual void handleRequestFromContext(const int &context, const int &request, const QList<QVariant> &args) override = 0;
    virtual void handleResponseFromContext(const int &context, const int &response, const QList<QVariant> &args) override = 0;

    virtual void handlePlayerScoresRequest() = 0;
signals:
    void sendGameModes(const QStringList &gameModes);
    void sendPlayerDetail(const QString &playerName, const QString &mailAdress);
    void sendPlayerScore(const QString &playerName, const int &score);
    void sendCalculatedScore(const int &point, const int &score);
    void sendInitialControllerValues(const QUuid &tournamentID,
                                     const int &keyPoint,
                                     const int &numberOfThrows,
                                     const QVector<QString> &players);
    void sendAssignedPlayerName(const QString &playerName);
    void sendCurrentTournamentKeyPoint(const int &point);
    void transmitResponse(const int &status, const QVariantList &args);
    void sendTournament(const QString &title,
                        const int &numberOfThrows,
                        const int &gameMode,
                        const int &keyPoint,
                        const int &playersCount);

    void sendRequestToContext(const int &context, const int &request, const QVariantList &args);
    void sendResponseToContext(const int &context, const int &response, const QVariantList &args);

private:
    DefaultDataInterface *_tournamentModelContext;
    PlayerContextInterface *_playerModelsContext;

};
#endif // ABSTRACTDATACONTEXT_H

