#ifndef REMOTEMODELSCONTEXT_H
#define REMOTEMODELSCONTEXT_H

#include "networkmanager.h"
#include "abstractmodelsservice.h"
#include <qjsonobject.h>
#include "itournamentbuilder.h"
#include "urlparser.h"
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <QJsonArray>
#include <QVariantList>

#include <iostream>

#define PRODUCTION
#ifdef PRODUCTION
#define API_HOST_URL "https://localhost:5001"
#elif
#define API_HOST_URL "Insert api url"
#endif

namespace RemoteContext
{
    class RemoteJsonObject : public QJsonObject
    {
    public:
        RemoteJsonObject(const std::initializer_list<QPair<QString,QJsonValue>>& list):
            QJsonObject(list)
        {

        }
        RemoteJsonObject()
        {}

        QByteArray toJson()
        {
            QJsonDocument document = QJsonDocument(*this);
            auto json = document.toJson(QJsonDocument::Compact);
            return json;
        }
    };
}

class RemoteModelsContext : public AbstractModelsService
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
    // AbstractModelsContext interface
    virtual void addDartsTournament(const QByteArray& json) override;
    virtual void assignPlayersToTournament(const QUuid &tournament, const QList<QUuid> &playersID) override;
    virtual void deleteTournaments(const QByteArray& json) override;
    virtual void getOrderedDartsPoints(const QUuid &tournamentId) override;
    virtual void handleRequestTournaments() override;
    virtual void handleRequestGameMode(const int &index) override;
    virtual void assembleDartsTournamentDataFromId(const QUuid &tournamentId) override;
    virtual void addDartsPoint(const QByteArray& json) override;
    void addDartsScore(const QByteArray &json) override;
    virtual void resetTournament(const QUuid &tournament) override;
    virtual void assembleDartsKeyValues(const QUuid &tournament) override;
    virtual void createPlayer(const QByteArray& json) override;
    virtual void deletePlayerFromIndex(const QByteArray& json) override;
    virtual void deletePlayersFromIndexes(const QByteArray& json) override;
    virtual void handleRequestPlayersDetails() override;
    virtual void assembleDartsPointIndexes(const QUuid &tournament) override;
private slots:
    void handleRecievedTournamentsReply();
    void handleAddFTPTournamentReply();
    void handleDeleteTournamentsReply();
    void handleRequestPlayersReply();
    void handleCreatePlayerResponse();
    void handleRequestGameModeReply();
    void handleRequestFtpDetailsReply();
    void handleFtpIndexesAndScores();
    void handleFtpTournamentMetaReply();
    void handleAddFtpScoreReply();
    void handleSetScoreHintReply();
    void tournamentResetReply();
    void deletePlayersReply();
    void recieveFtpScores();
private:

    enum ResponseCode {
        Error = 0x1,
        Success = 0x2
    };
    NetworkManager* _netMng = new NetworkManager(API_HOST_URL);

    // AbstractModelsContext interface
public:
    void hideDartsPoint(const QUuid &, const QUuid &, const int &, const int &) override;
    void revealPoint(const QUuid &, const QUuid &, const int &, const int &) override;
    void hideDartsScore(const QUuid &, const QUuid &, const int &) override;
    void revealScore(const QUuid &, const QUuid &, const int &) override;
    void assembleDartsIndexesAndScores(const QUuid &tournament) override;

    // AbstractModelsService interface
public:
    void assembleAssignedPlayerEntities(const QUuid &) override;
    void assembleAssignedPlayerPoints(const QUuid &) override;

    // AbstractModelsService interface
public:
    void assembleDartsTournamentWinnerIdAndName(const QUuid &) override;
};



#endif // REMOTEMODELSCONTEXT_H
