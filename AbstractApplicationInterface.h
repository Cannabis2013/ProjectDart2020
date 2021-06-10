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
    virtual void handleRequestForDartsSingleAttemptPoints() = 0;
    virtual void handleRequestForMultiAttemptScores()= 0;
    virtual void handleFTPDetails(const QByteArray& json) = 0;
    /*
     * Delete tournament
     */
    virtual void handleDeleteTournamentsRequest(const QByteArray& json) = 0;
    /*
     * UI requests to create/delete player from datacontext
     */
    virtual void handleCreatePlayer(const QByteArray& json) = 0;
    virtual void handleDeletePlayer(const QByteArray& json) = 0;
    virtual void handleDeletePlayersRequest(const QByteArray& json) = 0;
    /*
     * UI requests playerdetails from datacontext
     */
    virtual void requestPlayerDetails() = 0;
    virtual void handleSendGameModesRequest() const = 0;
    /*
     *  - Start/stop tournament
     *  - Reset and restart tournament
     */
    virtual void handleRequestStart() = 0;
    virtual void handleRequestStop() = 0;
    virtual void handleRestartTournament() = 0;
    /*
     * Handle UI user input
     *  - Users enters points to be stored in datacontext
     *  - In return, datacontext, in collaboration with gamecontroller, send current score to UI
     */
    virtual void handleDartsSingleAttemptInput(const QByteArray& json) = 0;
    virtual void handleDartsMultiAttemptInput(const QByteArray& json) = 0;
    virtual void handleUndoRequest() = 0;
    virtual void handleRedoRequest() = 0;
    virtual void handleControllerStateRequest() = 0;
    /*
     * Handle request for tournament meta information
     */
    virtual void assembleDartsTournamentValues() = 0;
    virtual void setDartsPointSingleAttempt(AbstractDartsController* controller) = 0;
    virtual void setDartsScoreMultiAttempt(AbstractDartsController* controller) = 0;
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
    void requestDartsSingleAttemptPoints();
    void requestDartsMultiAttemptScores();
    void setCurrentActiveTournament(const int &index);
    void sendDartsSingleAttemptPoint(const QByteArray& json);
    void sendDartsMultiAttemptScore(const QByteArray& json);
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
    void sendPlayers(const QVariantList& list);
    void createPlayerResponse(const bool &status);
    void requestAssembleFTPTournament();
    void tournamentAssembledAndStored();
    void tournamentCreatedOk();
    void sendAssembledMultiAttemptDartsScores(const QByteArray& json);
    void sendAssembledDartsSingleAttemptPoints(const QByteArray& json);
    // Controller states
    void controllerIsStopped();
    void dartsPointMultiColumnsInitialized();
    void dartsControllerRemovedSingleAttemptPoint(const QString& json);
    void dartsControllerRemovedMultiAttemptScore(const QString& json);
    void dartsControllerAddedDartsSingleAttemptPoint(const QByteArray& json);
    void dartsMultiAttemptScoreControllerIsInitalized();
    void dartsMultiAttemptScoreControllerIsReady();
    void dartsSingleAttemptPointControllerIsReady();
    void dartsControllerAddedDartsMultiAttemptScore(const QByteArray& json);
    void controllerAwaitsInput(const QByteArray& json);
    void dartsControllerIsReset();
    void controllerHasDeclaredAWinner(const QString& json);
    void assembleDartsController(const QByteArray& json,
                               AbstractApplicationInterface* applicationsInteface,
                               AbstractModelsService* modelsContextInterface);
};

#endif // APPLICATIONINTERFACE_H
