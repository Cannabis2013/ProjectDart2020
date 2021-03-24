#ifndef REMOTEMODELSCONTEXT_H
#define REMOTEMODELSCONTEXT_H

#include "networkmanager.h"
#include "abstractmodelscontext.h"
#include <qjsonobject.h>
#include "itournamentbuilder.h"
#include "tournamentbuildercontext.h"
#include "urlparser.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <QJsonArray>
#include <QVariantList>

#define PRODUCTION
#ifdef PRODUCTION
#define API_HOST_URL "https://localhost:5001"
#elif
#define API_HOST_URL "Insert api url"
#endif


class RemoteModelsContext : public AbstractModelsContext
{
    Q_OBJECT
public:
    // Create instance
    static RemoteModelsContext* createInstance()
    {
        return new RemoteModelsContext();
    }
    // Constructor
    RemoteModelsContext();
    // IResponseInterface interface
    virtual void transmitResponse(const int &response, const QVariantList &args) override;
    // AbstractModelsContext interface
    virtual void handleAddFTPTournament(const QString &title, const QVector<int> &data, const QVector<int> &playerIndexes) override;
    virtual void handleAssignPlayersToTournament(const QUuid &tournament, const QList<QUuid> &playersID) override;
    virtual void handleDeleteTournaments(const QVector<int> &indexes) override;
    virtual void handleRequestAssignedPlayers(const QUuid &tournament) override;
    virtual void handleRequestFTPScores(const QUuid &tournament) override;
    virtual void handleRequestTournaments() override;
    virtual void handleRequestGameMode(const int &index) override;
    virtual void assembleFTPMetaDataFromId(const QUuid &tournamentId) override;
    virtual void handleAddScore(const QUuid &tournament, const QUuid &player, const QVector<int> &dataValues, const bool &isWinnerDetermined) override;
    virtual void handleRequestSetScoreHint(const QUuid &tournament, const QUuid &player, const int &roundIndex, const int &throwIndex, const int &hint) override;
    virtual void handleResetTournament(const QUuid &tournament) override;
    virtual void handleRequestFtpDetails(const QUuid &tournament) override;
    virtual void handleCreatePlayer(const QString &name, const QString &mail) override;
    virtual void handleDeletePlayerFromIndex(const int &index) override;
    virtual void handleDeletePlayersFromIndexes(const QVector<int> &playerIndexes) override;
    virtual void handleRequestPlayersDetails() override;
    virtual void handleRequestPersistTournamentState() override;

private slots:
    void handleRecievedTournamentsReply();
    void handleAddFTPTournamentReply();
    void handleRequestPlayersReply();
    void handleCreatePlayerResponse();
    void handleRequestGameModeReply();
    void handleRequestFtpDetailsReply();
    void handleFtpTournamentMetaReply();
private:
    NetworkManager* _netMng = new NetworkManager(API_HOST_URL);
};

#endif // REMOTEMODELSCONTEXT_H
