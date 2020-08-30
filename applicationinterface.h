#ifndef PROJECTDARTINTERFACE_H
#define PROJECTDARTINTERFACE_H

#include <QtCore>

#include "abstracttournamentmodelscontext.h"
#include "abstractplayermodelscontext.h"
#include <abstractgamecontroller.h>
#include <idatamodelbuilder.h>
#include "iplayermodel.h"
#include "iplayerbuildercontext.h"
#include "IControllerBuilder.h"
#include "ipointlogisticinterface.h"
#include "iresponseinterface.h"

#include <qthreadpool.h>
#include <iostream>

using namespace std;

#define printVariable(var) #var
#define STATUS_ERROR -1;

typedef IPlayerModel<QUuid,QString> DefaultModelInterface;
typedef IPlayerBuilderParameters<QString,QUuid> DefaultParameters;
typedef IDataModelBuilder<DefaultModelInterface,DefaultParameters,IPlayerBuilderConfiguration> DefaultPlayerBuilder;

typedef IControllerBuilder<AbstractGameController, int> DefaultControllerBuilderInterface;

class ApplicationInterface : public QObject,
        public IResponseInterface<QVariantList>
{
    Q_OBJECT
public:
    enum GameModes {
        FirstToPost = 0x1,
        RoundLimit =0x2,
        Circular = 0x3,
        Cricket
    };
    enum Status{
        ContextNotInitialized = 0x4,
        ModelNotFound = 0x5,
        NoPlayersAssigned = 0x6,
        Success = 0x7,
        UnSuccess = 0x8
    };
    enum ModelDisplayHint{HiddenHint = 0x9,DisplayHint = 0xA, allHints = 0xB};

    enum ContextMode {LocalContext = 0x4, RemoteContext = 0x5};
    /*
     * Constructor
     */
    ApplicationInterface(AbstractTournamentModelsContext *tournamentModelsContext,
                         AbstractPlayerModelsContext *playerModelsContext,
                         DefaultControllerBuilderInterface *builder);
    ~ApplicationInterface();
    AbstractTournamentModelsContext *tournamentsModelContext() const;
    void setTournamentsModelContext(AbstractTournamentModelsContext *tournamentsModelContext);

    AbstractPlayerModelsContext *playerModelsContext() const;
    void setPlayerModelsContext(AbstractPlayerModelsContext *playerModelsContext);


public slots:
    void handleTournamentsRequest();
    void handleSetCurrentTournamentRequest(const int &index);
    /*
     * UI request data to populate scoreboard
     */
    void handleScoreBoardRequest();
    /*
     * Create tournament
     */
    void handleCreateTournament(const QString &title,
                                const int &numberOfThrows,
                                const int &gameMode,
                                const int &winCondition,
                                const int &keyPoint,
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
    void requestCreatePlayer(const QString &playerName, const QString &mail);
    void requestDeletePlayer(const int &index);
    void requestDeletePlayers(const QVector<int> &indexes);
    void requestDeleteTournaments(const QVector<int> &indexes);
    void requestTournaments();
    void requestPlayers();
    void sendAssignedPlayerIndexes(const QVariantList &indexes, const QUuid &tournament);
    void sendRequestedGameModes(const QStringList &gameModes);
    void sendPlayerDetail(const QString &playerName, const QString &mail);
    void sendPlayerScore(const QString &playerName,const int &point, const int &score);
    void sendAssignedPlayerName(const QString &playerName);
    void sendCurrentTournamentKeyPoint(const int &point);
    void sendRequestedTournament(const QString &title,
                                 const int &numberOfThrows,
                                 const int &gameMode,
                                 const int &keyPoint,
                                 const int &playersCount);
    void sendTournamentCandidate(const QString &title,
                                 const int &numberOfThrows,
                                 const int &gameMode,
                                 const int &winCondition,
                                 const int &keyPoint,
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

private slots:
    void processRecievedTournamentMetaData(const QString &title, const int &gameMode, const int &keyPoint, const QString &winnerName, const QStringList &assignedPlayerNames);
    void handleTournamentDetailsAndSetController(const QUuid &tournament,
                                                 const QString &winner,
                                                 const int &keyPoint,
                                                 const int &terminalKeyCode,
                                                 const int &numberOfThrows,
                                                 const int &gameMode,
                                                 const PlayerPairs &assignedPlayerPairs);
private:
    void connectControllerInterface();

    AbstractGameController *gameController() const;
    DefaultControllerBuilderInterface *controllerBuilder() const;

    int gameModeFromString(const QString &gameMode) const;

    QThread *_tournamentModelsThread;
    QThread *_playerModelsThread;

    IControllerBuilder<AbstractGameController, int> *_controllerBuilder;
    AbstractGameController *_gameController = nullptr;
    AbstractTournamentModelsContext *_tournamentsModelContext = nullptr;
    AbstractPlayerModelsContext *_playerModelsContext;

};

#endif // PROJECTDARTINTERFACE_H
