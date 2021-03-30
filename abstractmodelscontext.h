#ifndef ABSTRACTMODELCONTEXTINTERFACE_H
#define ABSTRACTMODELCONTEXTINTERFACE_H

#include <QObject>
#include <QUuid>
#include "iresponseinterface.h"

typedef QList<QPair<QUuid,QString>> PlayerPairs;

class AbstractModelsContext : public QObject,
        public IResponseInterface<QVariantList>
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
    virtual void addFTPTournament(const QString &title,
                                                  const QVector<int> &data,
                                                  const QVector<int> &playerIndexes) = 0;
    virtual void assignPlayersToTournament(const QUuid &tournament,
                                                 const QList<QUuid> &playersID) = 0;
    virtual void deleteTournaments(const QVector<int>&indexes) = 0;
    virtual void handleRequestAssignedPlayers(const QUuid &tournament) = 0;
    virtual void handleRequestFtpScores(const QUuid &tournament) = 0;
    virtual void handleRequestTournaments() = 0;
    virtual void handleRequestGameMode(const int &index) = 0;
    virtual void assembleFTPMetaDataFromId(const QUuid& tournament) = 0;
    virtual void addFtpScore(const QUuid &tournament,
                                const QUuid &player,
                                const int& roundIndex,
                                const int& setIndex,
                                const int& attemptIndex,
                                const int& point,
                                const int& score,
                                const int& keyCode,
                                const bool &isWinnerDetermined) = 0;
    virtual void setFtpScoreHint(const QUuid &tournament,
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
    virtual void createPlayer(const QString &name, const QString &mail) = 0;
    virtual void deletePlayerFromIndex(const int &index)= 0;
    virtual void deletePlayersFromIndexes(const QVector<int> &playerIndexes)= 0;
    virtual void handleRequestPlayersDetails() = 0;
    /*
     * Persist state
     */
    virtual void handleRequestPersistTournamentState() = 0;

signals:
    // IResponseInterface interface
    void transmitResponse(const int &response, const QVariantList &args);
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
    void sendTournamentMeta(const QVector<QString> &stringMetaData,
                            const QVector<int> numericMetaData,
                            const QVector<QString> &assignedPlayerNames);
    void requestAssembleTournament(const QUuid &tournament,
                                const int &gameMode);
    void sendTournamentIndexes(const int &roundIndex,
                               const int &setIndex,
                               const int &throwIndex,
                               const int &turnIndex,
                               const int &totalTurns ,
                               const QList<int> &playerScores);
    void scoreAddedToDataContext(const QUuid &playerID,
                                     const int &point,
                                     const int &score);
    void scoreNotAddedToDataContext(const QString& msg);
    void scoreHintUpdated(const QUuid &player, const int &point, const int &score);
    void scoreHintNotUpdated(const QUuid &player, QString err);
    void tournamentResetSuccess();
    void tournamentsDeletedSuccess(const bool &status);

    void sendTournaments(const QVariantList& list);
    /*
     * Player-models signals
     */
    void sendPlayersID(const QList<QUuid> &playersID);
    void sendTournamentFtpDetails(const QUuid& tournamentId,
                                  const QUuid& winnerId,
                                  const QVector<int> &values);
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
    void sendFtpIndexesAndScoreEntities(const int& totalTurns,
                                        const int& turns,
                                        const int& roundIndex,
                                        const int& setIndex,
                                        const int& attemptIndex,
                                        const QVector<PlayerEntity>& playerEntities,
                                        const QVector<ScoreEntity>& scoreEntities);
};

#endif // ABSTRACTMODELCONTEXTINTERFACE_H
