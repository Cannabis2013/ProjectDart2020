#ifndef PROJECTDARTINTERFACE_H
#define PROJECTDARTINTERFACE_H

#include <QtCore>

#include "abstracttournamentmodelscontext.h"
#include "abstractplayermodelscontext.h"
#include <abstractgamecontroller.h>
#include <itournamentmodelbuilder.h>
#include "iplayerbuildercontext.h"
#include "IControllerBuilder.h"
#include "ipointlogisticinterface.h"
#include "iresponseinterface.h"

#include <qthreadpool.h>
#include <iostream>

using namespace std;

#define printVariable(var) #var
#define STATUS_ERROR -1

typedef IPlayerModel<QUuid,QString> DefaultPlayerModelInterface;
typedef IPlayerBuilderParameters<QString,QUuid> DefaultParametersInterface;
typedef IControllerBuilder<AbstractGameController, int> IDefaultGameBuilder;

class ApplicationInterface : public QObject,
        public IResponseInterface<QVariantList>
{
    Q_OBJECT
public:
    enum GameModes {
        FirstToPost = 0x1,
        RoundLimit =0x2,
        Circular = 0x3,
        Cricket = 0x4
    };

    enum InputModes {
        PointInput = 0x5,
        ScoreInput = 0x6
    };

    enum ContextMode {
        LocalContext = 0x7,
        RemoteContext = 0x8
    };
    enum ModelDisplayHint{
        HiddenHint = 0x9,
        DisplayHint = 0xA,
        allHints = 0xB
    };

    /*
     * Destructor
     */
    ~ApplicationInterface();
    /*
     * Create and setup instance
     */
    static ApplicationInterface* createInstance();
    ApplicationInterface *setup();
    ApplicationInterface *useThreads();
    /*
     * Get/set TournamentModelsContext
     */
    AbstractTournamentModelsContext *tournamentsModelContext() const;
    ApplicationInterface* setTournamentsModelContext(AbstractTournamentModelsContext *tournamentsModelContext);
    /*
     * Get/set PlayerModelsContext
     */
    AbstractPlayerModelsContext *playerModelsContext() const;
    ApplicationInterface* setPlayerModelsContext(AbstractPlayerModelsContext *playerModelsContext);
    /*
     * Get/set GameControllerBuilder
     */
    IDefaultGameBuilder *controllerBuilder();
    ApplicationInterface *setControllerBuilder(IDefaultGameBuilder *builder);
public slots:
    void handleTournamentsRequest();
    void handleSetCurrentTournamentRequest(const int &index);
    /*
     * UI request data to populate scoreboard
     */
    void handleScoreBoardRequest();
    /*
     * Create tournament
     *
     * Data array allocates memmory locations in the following order:
     *  - [0] = Gamemode
     *  - [1] = Keypoint
     *  - [2] = KeyCode (win condition)
     *  - [3] = TableViewHint
     *  - [4] = InputMode
     *  - [5] = Number of throws
     */
    void handleCreateTournament(const QString &title,
                                const QList<int> &data,
                                const QVariantList &playerIndexes);
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
                                 const int &numberOfThrows,
                                 const int &gameMode,
                                 const int &keyPoint,
                                 const int &playersCount);
    void sendTournamentCandidate(const QString &title,
                                 const QList<int> &data,
                                 const QList<int> &playerIndexes);
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
    void sendTournamentMetaData(const QVariantList &meta);
    void removeScore(const QString &player);
    void sendTournamentDetails(const QUuid &tournament,
                               const QString &winner,
                               const int &keyPoint,
                               const int &terminalKeyCode,
                               const int &numberOfThrows,
                               const PlayerPairs &assignedPlayerPairs);
    void playersDeletedStatus(const bool &status);
    void tournamentsDeletedSuccess(const bool &status);

    void lastTournamentDetailsTransmitted();
    void lastPlayerDetailsTransmitted();
    void playerCreatedSuccess(const bool &status);

private slots:
    void processRecievedTournamentMetaData(const QString &title,
                                           const int &gameMode,
                                           const int &keyPoint,
                                           const int &tableViewHint,
                                           const QString &winnerName,
                                           const QStringList &assignedPlayerNames);
    void handleTournamentDetailsAndSetController(const QUuid &tournament,
                                                 const QString &winner,
                                                 const int &keyPoint,
                                                 const int &inputMode,
                                                 const int &terminalKeyCode,
                                                 const int &numberOfThrows,
                                                 const int &gameMode,
                                                 const PlayerPairs &assignedPlayerPairs);
private:
    void registerTypes();
    void connectModelInterfaces();
    void connectControllerInterface();

    void startTournamentModelsWorkerThread();
    void startPlayerModelsWorkerThread();
    void stopTournamentModelsWorkerThread();
    void stopPlayerModelsWorkerThread();
    AbstractGameController *gameController() const;
    IDefaultGameBuilder *controllerBuilder() const;

    QThread *_tournamentModelsThread = new QThread();
    QThread *_playerModelsThread = new QThread();
    QThread *_gameControllerThread = new QThread();

    IControllerBuilder<AbstractGameController, int> *_controllerBuilder;
    AbstractGameController *_gameController = nullptr;
    AbstractTournamentModelsContext *_tournamentModelsContext = nullptr;
    AbstractPlayerModelsContext *_playerModelsContext;

};

#endif // PROJECTDARTINTERFACE_H
