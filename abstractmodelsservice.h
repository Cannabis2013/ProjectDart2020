#ifndef ABSTRACTMODELCONTEXTINTERFACE_H
#define ABSTRACTMODELCONTEXTINTERFACE_H

#include <QObject>
#include <QUuid>

class AbstractModelsService : public QObject
{
    Q_OBJECT
public:
    // Public types
    typedef QPair<QUuid,QString> PlayerEntity;
    typedef QPair<QUuid,int> ScoreEntity;
    /*
     * Destructor
     */
    virtual ~AbstractModelsService() = default;
    /*
     * Tournament-models context interface..
     */
    /*
     * Handle requests from external context
     */

    virtual void addDartsTournament(const QByteArray& json) = 0;
    virtual void assignPlayersToTournament(const QUuid &tournament,
                                                 const QList<QUuid> &playersID) = 0;
    virtual void deleteTournaments(const QByteArray& json) = 0;
    virtual void getOrderedDartsPoints(const QUuid &tournament) = 0;
    virtual void handleRequestTournaments() = 0;
    virtual void handleRequestGameMode(const int &index) = 0;
    virtual void assembleDartsTournamentDataFromId(const QUuid& tournament) = 0;
    virtual void addDartsPoint(const QByteArray& json) = 0;
    virtual void addDartsScore(const QByteArray& json) = 0;
    virtual void hideDartsPoint(const QUuid&,
                                    const QUuid&,
                                    const int &,
                                    const int &) = 0;
    virtual void revealPoint(const QUuid &,
                                    const QUuid &,
                                    const int &,
                                    const int &) = 0;
    virtual void hideDartsScore(const QUuid&,
                                    const QUuid&,
                                    const int &) = 0;
    virtual void revealScore(const QUuid &,
                                    const QUuid &,
                                    const int &) = 0;
    virtual void resetTournament(const QUuid &tournament) = 0;
    virtual void assembleDartsKeyValues(const QUuid& tournament) = 0;
    // Initialize controller
    virtual void assembleDartsPointIndexes(const QUuid& tournament) = 0;
    virtual void assembleAssignedPlayerEntities(const QUuid&) = 0;
    virtual void assembleAssignedPlayerPoints(const QUuid&) = 0;
    virtual void assembleDartsTournamentWinnerIdAndName(const QUuid&) = 0;
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
    void tournamentResetSuccess();
    void tournamentResetFailed();
    void tournamentsDeletedStatus(const bool &status);

    void sendTournaments(const QByteArray& json);
    void dartsPointHiddenSucces(const QByteArray& json);
    void dartsPointRevealedSucces(const QByteArray& json);
    void dartsScoreHiddenSucces(const QByteArray& json);
    void dartsScoreRevealedSucces(const QByteArray& json);
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
    void playersDeletedStatus(const bool &status);
    void sendPlayers(const QVariantList& list);
    void createPlayerResponse(const bool &status);
    void tournamentModelsStatePersisted();
    void tournamentAssembledAndStored(const bool& status);
    // Initialize controller
    void sendDartsPointIndexesAsJson(const QByteArray& json);
    void sendAssignedPlayerIdsAndNamesAsJson(const QByteArray& json);
    void sendTournamentDartsPointsAsJson(const QByteArray& json);
    void sendDartsIndexesAndScoreValues(const QByteArray& json);
    void sendDartsTournamentWinnerIdAndName(const QByteArray& json);
    void sendDartsSingleAttemptPoints(const QByteArray& scores);
    void hideDartsPointSuccess(const QByteArray&);
    void revealDartsPointSuccess(const QByteArray&);
    void hideDartsScoreSuccess(const QByteArray&);
    void revealDartsScoreSuccess(const QByteArray&);
};

#endif // ABSTRACTMODELCONTEXTINTERFACE_H
