#ifndef ABSTRACTDARTSMODELSCONTEXT_H
#define ABSTRACTDARTSMODELSCONTEXT_H

#include <QObject>
#include <QUuid>
#include "ModelsContext/MCModelsSLAs/imodel.h"

class AbstractDartsModelsContext : public QObject
{
    Q_OBJECT
public:
    virtual ~AbstractDartsModelsContext() = default;
public slots:
    virtual void addDartsTournament(const QByteArray& json, const QVector<IModel<QUuid> *> &playerModels) = 0;
    virtual void deleteTournaments(const QVector<int>& indexes) = 0;
    virtual void getOrderedInputs(const QUuid &tournament) = 0;
    virtual void getTournaments() = 0;
    virtual void getGameMode(const int &index) = 0;
    virtual void createDartsMetaData(const QUuid& tournament) = 0;
    virtual void resetTournament(const QUuid &tournament) = 0;
    virtual void createDartsKeyValues(const QUuid& tournament) = 0;
    virtual void updateTournamentIndex(const QByteArray &json) = 0;
    virtual void setDartsTournamentWinner(const QByteArray& json) = 0;
    virtual void addInput(const QByteArray& json) = 0;
    virtual void hideInput(const QByteArray &json) = 0;
    virtual void revealInput(const QByteArray &json) = 0;
    virtual void createDartsValuesJson(const QUuid& tournament) = 0;
signals:
    void sendPlayerScore(const QString &player, const int &point, const int &score, const int &keyCode);
    void sendAssignedPlayerNames(const QVector<QString> &players);
    void confirmScoresTransmittedAndContextUpdated();
    void sendTournament(const QString &title, const int &gameMode, const int &playersCount);
    void sendTournamentMeta(const QByteArray& json);
    void requestAssembleTournament(const QUuid &tournament, const int &gameMode);
    void dartsValues(const QByteArray &indexJson, const QByteArray &inputsJson,
                     const QByteArray &playersJson, const QByteArray &winnerJson);
    void inputAdded(const QByteArray& json);
    void inputNotAdded(const QString& msg);
    void tournamentIndexUpdated();
    void hideInputSuccess(const QByteArray&);
    void revealInputSuccess(const QByteArray&);
    void tournamentResetSuccess();
    void tournamentResetFailed();
    void tournamentsDeletedStatus(const bool &status);
    void sendTournaments(const QByteArray& json);
    void setDartsTournamentWinnerSucces(const QByteArray& json);
    void sendDartsDetails(const QByteArray& json);
    void tournamentModelsStatePersisted();
    void tournamentCreatedAndPersisted();
    void sendOrderedInputs(const QByteArray& scores);
};
#endif // ABSTRACTDARTSMODELSCONTEXT_H
