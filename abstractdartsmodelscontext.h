#ifndef ABSTRACTDARTSMODELSCONTEXT_H
#define ABSTRACTDARTSMODELSCONTEXT_H

#include <QObject>
#include <QUuid>
#include <imodel.h>

class AbstractDartsModelsContext : public QObject
{
    Q_OBJECT
public:
    virtual ~AbstractDartsModelsContext() = default;
    virtual void addDartsTournament(const QByteArray& json, const QVector<const IModel<QUuid> *> &playerModels) = 0;
    virtual void deleteTournaments(const QVector<int>& indexes) = 0;
    virtual void getOrderedInputs(const QUuid &tournament) = 0;
    virtual void getTournaments() = 0;
    virtual void getGameMode(const int &index) = 0;
    virtual void createDartsMetaData(const QUuid& tournament) = 0;
    virtual void resetDartsPointTournament(const QUuid &tournament) = 0;
    virtual void createDartsKeyValues(const QUuid& tournament) = 0;
    virtual void setDartsTournamentWinner(const QByteArray& json) = 0;
    virtual void addInput(const QByteArray& json) = 0;
    virtual void hideInput(const QUuid& tournamentId,const QUuid& playerId,
                           const int &roundIndex,const int& attemptIndex) = 0;
    virtual void revealInput(const QUuid& tournamentId,const QUuid& playerId,
                             const int& roundIndex,const int& attemptIndex) = 0;
    virtual void createIndexes(const QUuid& tournament) = 0;
    virtual void getPlayerDetails(const QUuid &tournamentId) = 0;
    virtual void getPlayerInputs(const QUuid &tournamentId) = 0;
    virtual void getTournamentWinnerDetails(const QUuid &tournamentId) = 0;
signals:
    void sendPlayerScore(const QString &player, const int &point, const int &score, const int &keyCode);
    void sendAssignedPlayerNames(const QVector<QString> &players);
    void confirmScoresTransmittedAndContextUpdated();
    void sendTournament(const QString &title, const int &gameMode, const int &playersCount);
    void sendTournamentMeta(const QByteArray& json);
    void requestAssembleTournament(const QUuid &tournament, const int &gameMode);
    void pointAddedToDataContext(const QByteArray& json);
    void scoreAddedToDataContext(const QByteArray& json);
    void scoreNotAddedToDataContext(const QString& msg);
    void hideInputSuccess(const QByteArray&);
    void revealInputSuccess(const QByteArray&);
    void tournamentResetSuccess();
    void tournamentResetFailed();
    void tournamentsDeletedStatus(const bool &status);
    void sendTournaments(const QByteArray& json);
    void setDartsTournamentWinnerSucces(const QByteArray& json);
    void sendDartsDetails(const QByteArray& json, const int &inputHint);
    void tournamentModelsStatePersisted();
    void tournamentCreatedAndPersisted();
    void sendIndexesAsJson(const QByteArray& json);
    void sendAssignedPlayerDetails(const QByteArray& json);
    void sendInputs(const QByteArray& json);
    void sendDartsIndexesAndScoreValues(const QByteArray& json);
    void sendWinnerDetails(const QByteArray& json);
    void sendOrderedInputs(const QByteArray& scores);
};
#endif // ABSTRACTDARTSMODELSCONTEXT_H
