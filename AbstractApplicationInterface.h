#ifndef APPLICATIONINTERFACE_H
#define APPLICATIONINTERFACE_H

#include <qobject.h>
#include <quuid.h>
#include "abstractmodelsservice.h"
#include "abstractdartscontroller.h"
#include "iresponseinterface.h"
class AbstractApplicationInterface : public QObject
{
    Q_OBJECT
public slots:
    virtual void handleTournamentsRequest() = 0;
    /*
     * Set current tournament
     */
    virtual void handleSetCurrentTournamentRequest(const int &index) = 0;
    /*
     * UI request data to populate scoreboard
     */
    virtual void handleDartsDetails(const QByteArray& json) = 0;

    virtual void handleSendGameModesRequest() const = 0;
    /*
     * Handle request for tournament meta information
     */
    virtual void assembleDartsTournamentValues() = 0;
    virtual void setDartsPointController(AbstractDartsController* controller) = 0;
    virtual void setDartsScoreController(AbstractDartsController* controller) = 0;
signals:
    /*
     * ApplicationInterface interface
     */
    void requestWakeUp();
    void requestCreatePlayer(const QByteArray &json);
    void requestDeletePlayer(const QByteArray& json);
    void requestDeletePlayers(const QByteArray& json);
    void requestDeleteTournaments(const QByteArray& json);
    void requestTournaments();
    void requestPlayers();
    void sendAssignedPlayerIndexes(const QVariantList &indexes,
                                   const QUuid &tournament);
    void sendRequestedGameModes(const QStringList &gameModes);
    void sendRequestedTournament(const QString &title,
                                 const int &gameMode,
                                 const int &playersCount);
    void sendDartsDetails(const QByteArray& json);
    void sendGameModes(const QStringList &modes) const;
    void stateChanged();
    void sendInitialControllerValues(const QUuid &tournament,
                                     const int &keyPoint,
                                     const int &numberOfThrows,
                                     QList<QUuid> assignedPlayers);
    void requestOrderedDartsInputs();
    void requestDartsScores();
    void setCurrentActiveTournament(const int &index);
    void sendDartsPoint(const QByteArray& json);
    void sendDartsScore(const QByteArray& json);
    void requestStartGame();
    void requestStopGame();
    void requestTournamentReset();
    void requestControllerState();
    void requestUndo();
    void requestRedo();
    void requestCurrentTournamentId();
    void sendDartsTournamentData(const QByteArray& json);
    void removeScore(const QString &player);
    void playersDeletedStatus(const bool &status);
    void tournamentsDeletedSuccess(const bool &status);
    void sendTournaments(const QByteArray& json);
    void sendPlayers(const QByteArray& json);
    void createPlayerResponse(const bool &status);
    void requestAssembleFTPTournament();
    void tournamentAssembledAndStored();
    void tournamentCreatedOk();
    void sendOrderedDartsScores(const QByteArray& json);
    void sendOrderedDartsPoints(const QByteArray& json);
    // Controller states
    void controllerIsStopped();
    void dartsPointMultiColumnsInitialized();
    void dartsPointSingleColumnInitialized();
    void dartsScoreSingleColumnInitialized();
    void dartsScoreMultiColumnInitialized();
    void dartsControllerRemovedPoint(const QString& json);
    void dartsControllerRemovedScore(const QString& json);
    void addedDartsPoint(const QByteArray& json);
    void dartsScoreControllerIsReady();
    void dartsPointControllerIsReady();
    void addedDartsScore(const QByteArray& json);
    void controllerAwaitsInput(const QByteArray& json);
    void dartsControllerIsReset();
    void controllerHasDeclaredAWinner(const QString& json);
    void assembleDartsController(const QByteArray& json,
                               AbstractApplicationInterface* applicationsInteface,
                               AbstractModelsService* modelsContextInterface);
};

#endif // APPLICATIONINTERFACE_H
