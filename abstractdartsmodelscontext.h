#ifndef ABSTRACTDARTSMODELSCONTEXT_H
#define ABSTRACTDARTSMODELSCONTEXT_H

#include <QObject>
#include <QUuid>
#include <imodel.h>

class AbstractDartsModelsContext : public QObject
{
    Q_OBJECT
public:
    // Public types
    typedef QPair<QUuid,QString> PlayerEntity;
    typedef QPair<QUuid,int> ScoreEntity;
    // Destructor
    virtual ~AbstractDartsModelsContext() = default;
    // Darts general methods
    virtual void addDartsTournament(const QByteArray& json, const QVector<const IModel<QUuid> *> &playerModels) = 0;
    virtual void deleteTournaments(const QVector<int>& indexes) = 0;
    virtual void getOrderedDartsPoints(const QUuid &tournament) = 0;
    virtual void handleRequestTournaments() = 0;
    virtual void handleRequestGameMode(const int &index) = 0;
    virtual void createDartsMetaData(const QUuid& tournament) = 0;
    virtual void resetDartsPointTournament(const QUuid &tournament) = 0;
    virtual void resetDartsScoreTournament(const QUuid& tournamentId) = 0;
    virtual void createDartsKeyValues(const QUuid& tournament) = 0;
    virtual void setDartsTournamentWinner(const QByteArray& json) = 0;
    // Darts singleattempt point methods
    virtual void addDartsPoint(const QByteArray& json) = 0;
    virtual void hideDartsPoint(const QUuid&,
                                const QUuid&,
                                const int &,
                                const int &) = 0;
    virtual void revealPoint(const QUuid &,
                             const QUuid &,
                             const int &,
                             const int &) = 0;
    virtual void createDartsPointIndexes(const QUuid& tournament) = 0;
    virtual void createDartsScoreIndexes(const QUuid& tournament) = 0;
    virtual void createAssignedPlayerEntities(const QUuid&) = 0;
    virtual void createAssignedPlayerPoints(const QUuid&) = 0;
    virtual void createDartsTournamentWinnerIdAndName(const QUuid&) = 0;
    // Darts multiattempt score methods
    virtual void addDartsScore(const QByteArray& json) = 0;
    virtual void createAssignedPlayerScores(const QUuid&) = 0;
    virtual void hideDartsScore(const QUuid&,
                                    const QUuid&,
                                    const int &) = 0;
    virtual void revealScore(const QUuid &,
                                    const QUuid &,
                                    const int &) = 0;
signals:
    // Tournament-models signals
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
    void pointAddedToDataContext(const QByteArray& json);
    void scoreAddedToDataContext(const QByteArray& json);
    void scoreNotAddedToDataContext(const QString& msg);
    void hideDartsPointSuccess(const QByteArray&);
    void revealDartsPointSuccess(const QByteArray&);
    void hideDartsScoreSuccess(const QByteArray&);
    void revealDartsScoreSuccess(const QByteArray&);
    void tournamentResetSuccess();
    void tournamentResetFailed();
    void tournamentsDeletedStatus(const bool &status);
    void sendTournaments(const QByteArray& json);
    void setDartsTournamentWinnerSucces(const QByteArray& json);
    void sendDartsDetails(const QByteArray& json, const int &inputHint);
    // Tournaments related
    void tournamentModelsStatePersisted();
    void tournamentCreatedAndPersisted();
    // Initialize controller
    void sendDartsPointIndexesAsJson(const QByteArray& json);
    void sendDartsScoreIndexesAsJson(const QByteArray& json);
    void sendAssignedPlayerIdsAndNamesAsJson(const QByteArray& json);
    void sendTournamentDartsPointsAsJson(const QByteArray& json);
    void sendTournamentDartsScoresAsJson(const QByteArray& json);
    void sendDartsIndexesAndScoreValues(const QByteArray& json);
    void sendDartsTournamentWinnerIdAndName(const QByteArray& json);
    void sendOrderedDartsPoints(const QByteArray& scores);
};
#endif // ABSTRACTDARTSMODELSCONTEXT_H