#ifndef PROJECTDARTINTERFACE_H
#define PROJECTDARTINTERFACE_H

#include <QtCore>

#include <idatacontext.h>
#include <abstractgamecontroller.h>
#include <idatamodelbuilder.h>
#include "iplayermodel.h"
#include "iplayerbuildercontext.h"
#include "IControllerBuilder.h"
#include "abstractdatacontext.h"

#define printVariable(var) #var
#define STATUS_ERROR -1;

typedef IPlayerModel<QUuid,QString> DefaultModelInterface;
typedef IPlayerBuilderParameters<QString> DefaultParameters;
typedef IDataModelBuilder<DefaultModelInterface,DefaultParameters,IPlayerBuilderConfiguration> DefaultPlayerBuilder;
typedef IDataContext<QUuid,QList<QUuid>,QString,ITournamentBuilder> DefaultDataInterface;
typedef IController<QUuid,QString> GameControllerInterface;

typedef IControllerBuilder<AbstractGameController, int> DefaultControllerBuilderInterface;

class ApplicationInterface : public QObject, public IStatusInterface<QVariantList>
{
    Q_OBJECT
public:
    enum GameModes {
        FirstToPost = 0x1,
        RoundBased =0x2,
        CircularDart = 0x3
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
    ApplicationInterface(AbstractDataContext *dataContext, DefaultControllerBuilderInterface *_builder);


public slots:
    void handleTournamentsRequest();
    void handleSetCurrentTournamentRequest(const int &index);
    void handleScoreBoardRequest();
    void createTournament(const QString &title,
                                     const int &numberOfThrows,
                                     const QString &gameMode,
                                     const int &keyPoint,
                                     const QVariantList &playerIndexes);
    void createPlayer(const QString &userName, const QString &email);
    void requestPlayerDetails();
    void handleSendGameModesRequest() const;
    void requestStart();
    void requestStop();
    void handleUserInput(const int &point);
    void handleUndoRequest();
    void handleRedoRequest();
    void handleControllerStateRequest();

signals:
    void requestCreatePlayer(const QString &userName, const QString &mail);
    void requestTournaments();
    void requestPlayers();
    void sendAssignedPlayerIndexes(const QVariantList &indexes, const QUuid &tournament);
    void sendRequestedGameModes(const QStringList &gameModes);
    void sendPlayerDetail(const QString &userName, const QString &mail);
    void sendStatus(const int &status, const QVariantList &arguments) override;
    void sendPlayerScore(const QString &playerName, const int &score);
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
                                 const int &keyPoint,
                                 const QVariantList &playerIndexes);
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
    void sendPoint(const int &point);
    void startGame();
    void stopGame();
    void requestControllerState();
    void requestUndo();
    void requestRedo();

    void removeScore(const QString &player);

private:
    AbstractDataContext *dataContext() const;
    AbstractGameController *gameController() const;
    DefaultControllerBuilderInterface *controllerBuilder() const;

    int gameModeFromString(const QString &gameMode) const;

    IControllerBuilder<AbstractGameController, int> *_controllerBuilder;
    AbstractDataContext *_dataContext = nullptr;
    AbstractGameController *_gameController = nullptr;

};


#endif // PROJECTDARTINTERFACE_H




