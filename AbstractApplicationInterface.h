#ifndef APPLICATIONINTERFACE_H
#define APPLICATIONINTERFACE_H

#include <qobject.h>
#include <quuid.h>
#include "abstractmodelsservice.h"
#include "iresponseinterface.h"
class AbstractApplicationInterface : public QObject
{
    Q_OBJECT
public slots:
    virtual AbstractModelsService *modelsContextInterface() const = 0;
    virtual AbstractApplicationInterface* setModelsContextInterface(AbstractModelsService *modelsInterface) = 0;
    virtual void handleTournamentsRequest() = 0;
    /*
     * Set current tournament
     */
    virtual void handleSetCurrentTournamentRequest(const int &index) = 0;
    /*
     * UI request data to populate scoreboard
     */
    virtual void handleRequestForSingleThrowScoreData() = 0;
    virtual void handleRequestForMultiThrowScoreData() = 0;
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
    virtual void handleUserInput(const QByteArray& json) = 0;
    virtual void handleUndoRequest() = 0;
    virtual void handleRedoRequest() = 0;
    virtual void handleControllerStateRequest() = 0;
    /*
     * Handle request for tournament meta information
     */
    virtual void handleTournamentMetaRequest() = 0;
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
    void sendFTPDetails(const QByteArray& json);
    void sendGameModes(const QStringList &modes) const;
    void stateChanged();
    void sendInitialControllerValues(const QUuid &tournament,
                                     const int &keyPoint,
                                     const int &numberOfThrows,
                                     QList<QUuid> assignedPlayers);
    void requestSingleThrowPlayerScores();
    void requestDartsMultiAttemptScores();
    void setCurrentActiveTournament(const int &index);
    void sendPoint(const QByteArray& json);
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
    void sendTournaments(const QVariantList& list);
    void sendPlayers(const QVariantList& list);
    void createPlayerResponse(const bool &status);
    void requestAssembleFTPTournament();
    void tournamentAssembledAndStored(const bool &status);
    void tournamentCreatedOk();
    void FtpControllerInitializedAndReady(const bool& canUndo,
                                       const bool& canRedo,
                                       const int& roundIndex,
                                       const int& setIndex,
                                       const int& attemptIndex,
                                       const int& score,
                                       const QString& targetRow);
    void sendAssembledSingleFtpScores(const QByteArray& json);
    void sendAssembledMultiFtpScores(const QByteArray& json);
    // Controller states
    void controllerIsStopped();
    void controllerIsInitialized();
    void controllerAwaitsInput(const QString& json);
    void ftpControllerIsReset();
    void ftpControllerAddedAndPersistedScore(const QByteArray& json);
    void ftpControllerRemovedScore(const QString& json);
    void controllerHasDeclaredAWinner(const QString& json);
};

#endif // APPLICATIONINTERFACE_H
