#ifndef REMOTEMODELSCONTEXT_H
#define REMOTEMODELSCONTEXT_H

#include "networkmanager.h"
#include "abstractmodelscontext.h"
#include <qjsonobject.h>
#include "itournamentbuilder.h"
#include "tournamentbuildercontext.h"

#define PRODUCTION
#ifdef PRODUCTION
#define API_HOST_URL "https://localhost:5001"
#elif
#define API_HOST_URL "Insert api url"
#endif


class RemoteModelsContext : public AbstractModelsContext
{
public:
    // Constructor
    RemoteModelsContext();
    // IResponseInterface interface
    virtual void transmitResponse(const int &response, const QVariantList &args) override;
    // AbstractModelsContext interface
    virtual void handleRequestForAddFTPTournament(const QString &title, const QVector<int> &data, const QVector<int> &playerIndexes) override;
    virtual void handleAssignPlayersToTournament(const QUuid &tournament, const QList<QUuid> &playersID) override;
    virtual void handleDeleteTournaments(const QVector<int> &indexes) override;
    virtual void handleRequestAssignedPlayers(const QUuid &tournament) override;
    virtual void handleTransmitPlayerScores(const QUuid &tournament) override;
    virtual void handleTransmitTournamentData() override;
    virtual void handleRequestTournamentGameMode(const int &index) override;
    virtual void assembleTournamentMetaDataFromId(const QUuid &tournament) override;
    virtual void handleAddScore(const QUuid &tournament, const QUuid &player, const QVector<int> &dataValues, const bool &isWinnerDetermined) override;
    virtual void handleRequestSetScoreHint(const QUuid &tournament, const QUuid &player, const int &roundIndex, const int &throwIndex, const int &hint) override;
    virtual void handleResetTournament(const QUuid &tournament) override;
    virtual void handleRequestFTPDetails(const QUuid &tournament) override;
    virtual void handleCreatePlayer(const QString &name, const QString &mail) override;
    virtual void handleDeletePlayerFromIndex(const int &index) override;
    virtual void handleDeletePlayersFromIndexes(const QVector<int> &playerIndexes) override;
    virtual void handleRequestPlayersDetails() override;
    virtual void handleRequestPersistTournamentState() override;

private:
    NetworkManager* _netMng = new NetworkManager(API_HOST_URL);
};

#endif // REMOTEMODELSCONTEXT_H
