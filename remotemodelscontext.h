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
        {

        }

        QByteArray toJson()
        {
            QJsonDocument document = QJsonDocument(*this);
            auto json = document.toJson(QJsonDocument::Compact);
            return json;
        }
    };
}

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
    virtual void addFTPTournament(const QString &title, const QVector<int> &data, const QVector<int> &playerIndexes) override;
    virtual void assignPlayersToTournament(const QUuid &tournament, const QList<QUuid> &playersID) override;
    virtual void deleteTournaments(const QVector<int> &indexes) override;
    virtual void handleRequestAssignedPlayers(const QUuid &tournament) override;
    virtual void handleRequestFtpScores(const QUuid &tournament) override;
    virtual void handleRequestTournaments() override;
    virtual void handleRequestGameMode(const int &index) override;
    virtual void assembleFTPMetaDataFromId(const QUuid &tournamentId) override;
    virtual void addFtpScore(const QUuid &tournament,
                                const QUuid &player,
                                const int& roundIndex,
                                const int& setIndex,
                                const int& attemptIndex,
                                const int& point,
                                const int& score,
                                const int& keyCode,
                                const bool &isWinnerDetermined) override;
    virtual void setFtpScoreHint(const QUuid &tournament, const QUuid &player, const int &roundIndex, const int &attemptIndex, const int &hint) override;
    virtual void resetTournament(const QUuid &tournament) override;
    virtual void assembleFtpKeyValues(const QUuid &tournament) override;
    virtual void createPlayer(const QString &name, const QString &mail) override;
    virtual void deletePlayerFromIndex(const int &index) override;
    virtual void deletePlayersFromIndexes(const QVector<int> &playerIndexes) override;
    virtual void handleRequestPlayersDetails() override;
    virtual void assembleFtpIndexesAndScores(const QUuid &tournament) override;
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
private:
    NetworkManager* _netMng = new NetworkManager(API_HOST_URL);
};

#endif // REMOTEMODELSCONTEXT_H
