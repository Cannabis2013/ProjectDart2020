#ifndef PROJECTDARTINTERFACE_H
#define PROJECTDARTINTERFACE_H

#include <QtCore>
#include <qthreadpool.h>
#include <iostream>

#include "tournamentmodelscontextinterface.h"
#include "playermodelscontextinterface.h"
#include "abstractgamecontroller.h"
#include "itournamentmodelbuilder.h"
#include "iplayerbuildercontext.h"
#include "abstractcontrollerbuilder.h"
#include "iresponseinterface.h"
#include "abstractmodelscontextinterface.h"

using namespace std;

#define printVariable(var) #var
#define STATUS_ERROR -1

class DartApplication : public QObject,
        public IResponseInterface<QVariantList>
{
    Q_OBJECT
public:

    /*
     * Should be located in an eventual 'ModelsContextBuilder'
     * enum ContextMode {
        LocalContext = 0x7,
        RemoteContext = 0x8
    };
     */
    /*
     * Destructor
     */
    ~DartApplication();
    /*
     * Create and setup instance
     */
    static DartApplication* createInstance();
    DartApplication *setup();
    DartApplication *useThreads();
    /*
     * Get/set modelcontext interface
     */
    AbstractModelsContextInterface* modelsContextInterface();
    DartApplication* setModelsContextInterface(AbstractModelsContextInterface* context);
    /*
     * Get/set GameControllerBuilder
     */
    AbstractControllerBuilder* controllerBuilder();
    DartApplication *setControllerBuilder(AbstractControllerBuilder *builder);
    AbstractModelsContextInterface *modelsInterface() const;
    DartApplication* setModelsInterface(AbstractModelsContextInterface *modelsInterface);

public slots:
    void handleTournamentsRequest();
    /*
     * Set current tournament
     */
    void handleSetCurrentTournamentRequest(const int &index);
    /*
     * UI request data to populate scoreboard
     */
    void handleScoreBoardRequest();
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
    void handleFTPDetails(const QString &title,
                                const QVector<int> &data,
                                const QVector<int> &playerIndexes);
    /*
     * Delete tournament
     */
    void handleDeleteTournamentsRequest(const QVariantList &indexes);
    /*
     * UI requests to create/delete player from datacontext
     */
    void handleCreatePlayer(const QString &playerName, const QString &email);
    void handleDeletePlayer(const int &index);
    void handleDeletePlayersRequest(const QVariantList &args);
    /*
     * UI requests playerdetails from datacontext
     */
    void requestPlayerDetails();
    void handleSendGameModesRequest() const;
    /*
     *  - Start/stop tournament
     *  - Reset and restart tournament
     */
    void handleRequestStart();
    void handleRequestStop();
    void handleRestartTournament();
    /*
     * Handle UI user input
     *  - Users enters points to be stored in datacontext
     *  - In return, datacontext, in collaboration with gamecontroller, send current score to UI
     */
    void handleUserInput(const int &point, const int &pressedModfier);
    void handleUndoRequest();
    void handleRedoRequest();
    void handleControllerStateRequest();
    /*
     * Handle request for tournament meta information
     */
    void handleTournamentMetaRequest();
signals:
    /*
     * Iresponse interface
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
    void requestPlayerScores();
    void setCurrentActiveTournament(const int &index);
    void sendPoint(const int &point, const int &pressedModifier);
    void requestStartGame();
    void requestStopGame();
    void requestTournamentReset();
    void requestControllerState();
    void requestUndo();
    void requestRedo();
    void requestTournamentMetaData();
    void sendFTPTournamentMetaData(const QVector<QString> &stringMetaData,
                                const QVector<int> numericMetaData,
                                const QVector<QString> &assignedPlayerNames);
    void removeScore(const QString &player);
    void sendTournamentDetails(const QUuid &tournament,
                               const QString &winner,
                               const PlayerPairs &assignedPlayerPairs);
    void playersDeletedStatus(const bool &status);
    void tournamentsDeletedSuccess(const bool &status);

    void lastTournamentDetailsTransmitted();
    void lastPlayerDetailsTransmitted();
    void playerCreatedSuccess(const bool &status);

private slots:
    void setGameController(AbstractGameController* controller);
private:
    // Register and connect interfaces related..
    void registerTypes();
    void connectModelInterfaces();
    void connectControllerInterface();
    // Clear controller..
    void clearGameController();

    // Threads related..
    bool usingThreads() const;
    void setUsingThreads(bool usingThreads);
    void startModelsContextInterfaceThread();
    void stopModelsInterfaceThread();
    // Builders related..
    AbstractGameController *gameController() const;
    AbstractControllerBuilder* controllerBuilder() const;
    // Application state member variables
    bool _usingThreads;
    QThread* _modelsContextInterfaceThread = new QThread();
    QThread *_gameControllerThread = new QThread();
    AbstractControllerBuilder *_controllerBuilder;
    AbstractModelsContextInterface* _modelsInterface;
    AbstractGameController *_gameController = nullptr;
};

#endif // PROJECTDARTINTERFACE_H
