#ifndef ABSTRACTMODELCONTEXTINTERFACE_H
#define ABSTRACTMODELCONTEXTINTERFACE_H

#include <QObject>
#include <QUuid>
#include "iresponseinterface.h"

typedef QList<QPair<QUuid,QString>> PlayerPairs;

class AbstractModelsContext : public QObject
{
    Q_OBJECT
public:
    // Public types
    typedef QPair<QUuid,QString> PlayerEntity;
    typedef QPair<QUuid,int> ScoreEntity;
    /*
     * Destructor
     */
    virtual ~AbstractModelsContext() = default;
    /*
     * Tournament-models context interface..
     */
    /*
     * Handle requests from external context
     */
    virtual void addFTPTournament(const QByteArray& json) = 0;
    virtual void assignPlayersToTournament(const QUuid &tournament,
                                                 const QList<QUuid> &playersID) = 0;
    virtual void deleteTournaments(const QByteArray& json) = 0;
    virtual void handleRequestFtpScores(const QUuid &tournament) = 0;
    virtual void handleRequestTournaments() = 0;
    virtual void handleRequestGameMode(const int &index) = 0;
    virtual void assembleFtpMetaDataFromId(const QUuid& tournament) = 0;
    virtual void addDartsPoint(const QByteArray& json) = 0;
    virtual void set501MultiPointHint(const QUuid &tournament,
                                               const QUuid &player,
                                               const int &roundIndex,
                                               const int &throwIndex,
                                               const int &hint) = 0;
    virtual void resetTournament(const QUuid &tournament) = 0;
    /*
     * Assemble and send basic ftp tournament values
     */
    virtual void assembleFtpKeyValues(const QUuid& tournament) = 0;
    virtual void assembleFtpIndexesAndScores(const QUuid& tournament) = 0;
    /*
     * Player-models context interface..
     */
    virtual void createPlayer(const QByteArray &json) = 0;
    virtual void deletePlayerFromIndex(const QByteArray& json)= 0;
    virtual void deletePlayersFromIndexes(const QByteArray& json)= 0;
    virtual void handleRequestPlayersDetails() = 0;

signals:
    /*
     * Tournament-models signals
     */
    void sendPlayerScore(const QString &player,
                         const int &point,
                         const int &score,
                         const int &keyCode);

    void sendAssignedPlayerNames(const QVector<QString> &players);
    void confirmScoresTransmittedAndContextUpdated();
    void sendTournament(const QString &title,
                        const int &gameMode,
                        const int &playersCount);
    void sendTournamentMeta(const QByteArray& json);
    void requestAssembleTournament(const QUuid &tournament,
                                const int &gameMode);
    void sendTournamentIndexes(const int &roundIndex,
                               const int &setIndex,
                               const int &throwIndex,
                               const int &turnIndex,
                               const int &totalTurns ,
                               const QList<int> &playerScores);
    void scoreAddedToDataContext(const QByteArray& json);
    void scoreNotAddedToDataContext(const QString& msg);
    void scoreHintUpdated(const QByteArray& json);
    void scoreHintNotUpdated(const QUuid &player, QString err);
    void tournamentResetSuccess();
    void tournamentResetFailed();
    void tournamentsDeletedStatus(const bool &status);

    void sendTournaments(const QVariantList& list);
    /*
     * Player-models signals
     */
    void sendPlayersID(const QList<QUuid> &playersID);
    void sendTournamentFtpDetails(const QByteArray& json);
    void sendProcessedTournamentMetaData(const QString &title,
                                         const int &gameMode,
                                         const int &keyPoint,
                                         const int &tableViewHint,
                                         const int &inputMode,
                                         const QString &winner,
                                         const QStringList &assignedPlayerNames);
    void sendCurrentAssignedPlayerPairs(const QUuid &tournament,
                                        const PlayerPairs &playerPairs);
    void sendProcessedTournamentDetails(const QString &title,
                                        const QList<int> &data,
                                        const QList<QUuid> &playersID);
    void playersDeletedStatus(const bool &status);
    void sendPlayers(const QVariantList& list);
    void createPlayerResponse(const bool &status);
    void tournamentModelsStatePersisted();
    void tournamentAssembledAndStored(const bool& status);
    void sendFtpIndexesAndScoreEntities(const QByteArray& json);
    void sendFtpMultiScores(const QByteArray& scores);
};

#endif // ABSTRACTMODELCONTEXTINTERFACE_H
