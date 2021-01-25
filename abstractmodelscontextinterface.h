#ifndef ABSTRACTMODELCONTEXTINTERFACE_H
#define ABSTRACTMODELCONTEXTINTERFACE_H

#include <QObject>
#include <QUuid>
#include "iresponseinterface.h"

typedef QList<QPair<QUuid,QString>> PlayerPairs;

class AbstractModelsContextInterface : public QObject,
        public IResponseInterface<QVariantList>
{
    Q_OBJECT
public:
    /*
     * Destructor
     */
    virtual ~AbstractModelsContextInterface() = default;
    /*
     * Tournament-models context interface..
     */
    /*
     * Handle requests from external context
     */
    virtual void handleRequestForAddFTPTournament(const QString &title,
                                                  const QVector<int> &data,
                                                  const QVector<int> &playerIndexes) = 0;
    virtual void handleAssignPlayersToTournament(const QUuid &tournament,
                                                 const QList<QUuid> &playersID) = 0;
    virtual void handleDeleteTournaments(const QVector<int>&indexes) = 0;
    virtual void handleRequestAssignedPlayers(const QUuid &tournament) = 0;
    virtual void handleTransmitPlayerScores(const QUuid &tournament) = 0;
    virtual void handleTransmitTournamentData() = 0;
    virtual void handleRequestTournamentGameMode(const int &index) = 0;
    virtual void handleRequestForFTPMetaData(const QUuid& tournament) = 0;
    virtual void handleAddScore(const QUuid &tournament,
                  const QUuid &player,
                  const QList<int> &dataValues,
                  const bool &isWinnerDetermined) = 0;
    virtual void handleRequestSetScoreHint(const QUuid &tournament,
                                               const QUuid &player,
                                               const int &roundIndex,
                                               const int &throwIndex,
                                               const int &hint) = 0;
    virtual void handleResetTournament(const QUuid &tournament) = 0;
    /*
     * Send tournament values
     */
    virtual void handleRequestFTPDetails(const QUuid& tournament) = 0;
    /*
     * Player-models context interface..
     */
    virtual void handleCreatePlayer(const QString &name, const QString &mail) = 0;
    virtual void handleDeletePlayerFromIndex(const int &index)= 0;
    virtual void handleDeletePlayersFromIndexes(const QVector<int> &playerIndexes)= 0;
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
    void scoreHintUpdated(const QUuid &player, const int &point, const int &score);
    void scoreHintNotUpdated(const QUuid &player, const char *err);
    void tournamentResetSuccess();
    void tournamentsDeletedSuccess(const bool &status);

    void lastTournamentTransmitted();
    /*
     * Player-models signals
     */
    void sendPlayerDetails(const QString &playerName, const QString &mail);
    void sendPlayersID(const QList<QUuid> &playersID);
    void sendTournamentFTPDetails(const QVector<QUuid>& idAndWinner,
                                  const QVector<int> &values,
                                  const QVector<QUuid> &userIds,
                                  const QVector<QString> &playerNames);
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
    void lastPlayerDetailTransmitted();
    void confirmPlayerCreated(const bool &status);
    void tournamentModelsStatePersisted();
};

#endif // ABSTRACTMODELCONTEXTINTERFACE_H
