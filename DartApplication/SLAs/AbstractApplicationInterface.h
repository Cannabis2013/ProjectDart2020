#ifndef ABSTRACTAPPLICATIONINTERFACE_H
#define ABSTRACTAPPLICATIONINTERFACE_H
#include "DartsModelsContext//SLAs/abstractdartsmodelscontext.h"
#include "DartsController/ControllerSLA/abstractdartscontroller.h"
class AbstractApplicationInterface : public QObject
{
    Q_OBJECT
public:
    Q_INVOKABLE virtual void addDartsTournaments(const QByteArray &json) = 0;
public slots:
    virtual void setDartsController(AbstractGameController* controller) = 0;
signals:
    void requestWakeUp();
    void requestDeleteTournaments(const QVector<int>& indexes);
    void requestTournaments();
    void requestPlayers();
    void sendRequestedTournament(const QString &title, const int &gameMode, const int &playersCount);
    void sendDartsDetails(const QByteArray& json);
    void sendGameModes(const QStringList &modes);
    void requestDartsScores();
    void setCurrentActiveTournament(const int &index);
    void requestTournamentReset();
    void dartsUndo();
    void dartsRedo();
    void requestCurrentTournamentId();
    void removeScore(const QString &player);
    void sendDartsTournamentData(const QByteArray& json);
    void tournamentsDeletedSuccess(const bool &status);
    void sendTournaments(const QByteArray& json);
    void sendPlayers(const QByteArray& json);
    void tournamentCreatedSuccess();
    void sendDartsScores(const QByteArray& json);
    void sendOrderedDartsInputs(const QByteArray& json);
    void requestCreatePlayer(const QByteArray &json);
    void requestDeletePlayers(const QVector<int> &indexes);
    void playerAddedSucces();
    void playerAddedError(const QString &msg);
    void playersDeletedStatus(const bool &status);
    void requestControllerState();
    void addUserInput(const QByteArray& json);
    void requestStartGame();
    void requestStopGame();
    void dartsNextTurn();
    void controllerStopped();
    void controllerReady();
    void dartsPointSingleColumnInitialized();
    void dartsScoreSingleColumnInitialized();
    void dartsScoreMultiColumnInitialized();
    void sendDartsScore(const QByteArray& json);
    void updateDartsTurnValues(const QByteArray& json);
    void dartsControllerIsReset();
    void winnerFound(const QString& json);
    void createDartsController(const QByteArray& json, AbstractApplicationInterface* application,
                               AbstractDartsModelsContext* modelsContext);
};
#endif // ABSTRACTAPPLICATIONINTERFACE_H
