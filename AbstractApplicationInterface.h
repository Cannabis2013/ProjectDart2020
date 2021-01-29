#ifndef APPLICATIONINTERFACE_H
#define APPLICATIONINTERFACE_H

#include <qobject.h>
#include "iresponseinterface.h"
#include <quuid.h>
class AbstractApplicationInterface : public QObject,
        public IResponseInterface<QVariantList>
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
    virtual void handleRequestForSingleThrowScoreData() = 0;
    virtual void handleRequestForMultiThrowScoreData() = 0;
    /*
     * Create tournament
     *
     *  Data array allocates memmory locations in the following order:
     *   - [0] = Gamemode
     *   - [1] = Keypoint
     *   - [2] = KeyCode (win condition)
     *   - [3] = TableViewHint
     *   - [4] = InputMode
     *   - [5] = Number of throws
     */
    virtual void handleFTPDetails(const QString &title,
                                const QVector<int> &data,
                                const QVector<int> &playerIndexes) = 0;
    /*
     * Delete tournament
     */
    virtual void handleDeleteTournamentsRequest(const QVariantList &indexes) = 0;
    /*
     * UI requests to create/delete player from datacontext
     */
    virtual void handleCreatePlayer(const QString &playerName, const QString &email) = 0;
    virtual void handleDeletePlayer(const int &index) = 0;
    virtual void handleDeletePlayersRequest(const QVariantList &args) = 0;
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
    virtual void handleUserInput(const int &point, const int &pressedModfier) = 0;
    virtual void handleUndoRequest() = 0;
    virtual void handleRedoRequest() = 0;
    virtual void handleControllerStateRequest() = 0;
    /*
     * Handle request for tournament meta information
     */
    virtual void handleTournamentMetaRequest() = 0;
    /*
     * Handle request for tournament persist
     */
    virtual void handlePersistTournamentRequest() = 0;
signals:
    /*
     * IResponse interface
     */
    void transmitResponse(const int &status, const QVariantList &arguments) override;
    /*
     * ApplicationInterface interface
     */
    void requestWakeUp();
    void requestCreatePlayer(const QString &playerName, const QString &mail);
    void requestDeletePlayer(const int &index);
    void requestDeletePlayers(const QVector<int> &indexes);
    void requestDeleteTournaments(const QVector<int> &indexes);
    void requestTournaments();
    void requestPlayers();
    void sendAssignedPlayerIndexes(const QVariantList &indexes, const QUuid &tournament);
    void sendRequestedGameModes(const QStringList &gameModes);
    void sendPlayerDetail(const QString &playerName, const QString &mail);
    void sendPlayerScore(const QString &playerName,const int &point, const int &score, const int &keyCode);
    void sendAssignedPlayerName(const QString &playerName);
    void sendCurrentTournamentKeyPoint(const int &point);
    void sendRequestedTournament(const QString &title,
                                 const int &gameMode,
                                 const int &playersCount);
    void sendFTPDetails(const QString &title,
                        const QVector<int> &data,
                        const QVector<int> &playerIndexes);
    void sendInformalControllerValues(const int &roundIndex,
                                      const QString &playerName,
                                      const bool &undoAvailable,
                                      const bool &redoAvailable);
    void sendGameModes(const QStringList &modes) const;
    void stateChanged();
    void sendInitialControllerValues(const QUuid &tournament,
                                     const int &keyPoint,
                                     const int &numberOfThrows,
                                     QList<QUuid> assignedPlayers);
    void requestSingleThrowPlayerScores();
    void requestMultiThrowPlayerScores();
    void setCurrentActiveTournament(const int &index);
    void sendPoint(const int &point, const int &pressedModifier);
    void requestStartGame();
    void requestStopGame();
    void requestTournamentReset();
    void requestControllerState();
    void requestUndo();
    void requestRedo();
    void requestCurrentTournamentId();
    void sendFTPTournamentMetaData(const QVector<QString> &stringMetaData,
                                   const QVector<int> numericMetaData,
                                   const QVector<QString> &assignedPlayerNames);
    void removeScore(const QString &player);
    void playersDeletedStatus(const bool &status);
    void tournamentsDeletedSuccess(const bool &status);

    void lastTournamentDetailsTransmitted();
    void lastPlayerDetailsTransmitted();
    void playerCreatedSuccess(const bool &status);
    void requestPersistTournament();
    void requestAssembleFTPTournament();

};

#endif // APPLICATIONINTERFACE_H
