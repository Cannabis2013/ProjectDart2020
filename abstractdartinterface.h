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

typedef IPlayerModel<QUuid,QString> DefaultModelInterface;
typedef IPlayerBuilderParameters<QString> DefaultParameters;
typedef IDataModelBuilder<DefaultModelInterface,DefaultParameters,IPlayerBuilderConfiguration> DefaultPlayerBuilder;
typedef IDataContext<QUuid,QList<QUuid>,QString,ITournamentBuilder> DefaultDataInterface;
typedef IController<QUuid,QString> GameControllerInterface;

typedef IControllerBuilder<AbstractGameController, int> DefaultControllerBuilderInterface;

class AbstractDartInterface : public QObject, public IStatusInterface<QVariantList>
{
    Q_OBJECT
public:
    enum GameModes {
        FirstToPost = 0x1,
        RoundBased =0x2,
        CircularDart = 0x3
    };

    enum ContextMode {LocalContext = 0x4, RemoteContext = 0x5};
    AbstractDartInterface(AbstractDataContext *dataContext, DefaultControllerBuilderInterface *_builder)
    {
        _dataContext = dataContext;
        _gameController = _builder->buildController(GameModes::FirstToPost,ContextMode::LocalContext);

        // Request tournaments -> Send tournaments back to UI
        connect(this,&AbstractDartInterface::requestTournaments,_dataContext,&AbstractDataContext::sendRequestedTournaments);
        connect(_dataContext,&AbstractDataContext::sendTournament,this,&AbstractDartInterface::sendRequestedTournament);
        // Set current tournament -> Initialize controller indexes
        connect(this,&AbstractDartInterface::setCurrentActiveTournament,_dataContext,&AbstractDataContext::handleSetCurrentTournament);
        connect(_dataContext,&AbstractDataContext::sendInitialControllerValues,_gameController,&AbstractGameController::initializeController);
        connect(_gameController,&AbstractGameController::requestInitialIndexes,_dataContext,&AbstractDataContext::handleInitialIndexesRequest);
        connect(_dataContext,&AbstractDataContext::sendInitialControllerIndexes,_gameController,&AbstractGameController::initializeIndexes);
        // Notify UI regarding context states
        connect(_gameController,&AbstractGameController::sendStatus,this,&AbstractDartInterface::sendStatus);
        connect(_dataContext,&AbstractDataContext::sendStatus,this,&AbstractDartInterface::sendStatus);
        // Game UI needs to be updated. The following connection until next comment ensures exactly that
        connect(this,&AbstractDartInterface::requestPlayerScores,_gameController,&AbstractGameController::handleCurrentTournamentRequest);
        connect(_gameController,&AbstractGameController::sendCurrentTournament,_dataContext,&AbstractDataContext::handleSendPlayerScoresRequest);
        connect(_dataContext,&AbstractDataContext::sendCurrentTournamentKeyPoint,this,&AbstractDartInterface::sendCurrentTournamentKeyPoint);
        connect(_dataContext,&AbstractDataContext::sendAssignedPlayerName,this,&AbstractDartInterface::sendAssignedPlayerName);
        connect(_dataContext,&AbstractDataContext::sendPlayerScore,this,&AbstractDartInterface::sendPlayerScore);
        // Datacontext has to notify controller about its state
        connect(_dataContext,&AbstractDataContext::sendContextStatus,_gameController,&AbstractGameController::handleReplyFromContext);
        // UI request creation of a new tournament
        connect(this,&AbstractDartInterface::sendTournamentCandidate,_dataContext,&AbstractDataContext::createTournament);
        // UI request creation of a new player
        connect(this,&AbstractDartInterface::requestCreatePlayer,_dataContext,&AbstractDataContext::createPlayer);
        // Request player details
        connect(this,&AbstractDartInterface::requestPlayers,_dataContext,&AbstractDataContext::handleSendPlayerDetailsRequest);
        // Send player details to UI
        connect(_dataContext,&AbstractDataContext::sendPlayerDetail,this,&AbstractDartInterface::sendPlayerDetail);
        // Request start -> Start game
        connect(this,&AbstractDartInterface::requestStart,_gameController,&AbstractGameController::start);
        connect(this,&AbstractDartInterface::requestStop,_gameController,&AbstractGameController::stop);
    }


public slots:
    virtual void handleTournamentsRequest(){
        emit requestTournaments();
    }
    virtual void handleSetCurrentTournamentRequest(const int &index)
    {
        emit setCurrentActiveTournament(index);
    }
    virtual void handleScoreBoardRequest()
    {
        emit requestPlayerScores();
    }
    virtual void createTournament(const QString &title,
                                     const int &numberOfThrows,
                                     const int &maxPlayers,
                                     const int &gameMode,
                                     const int &keyPoint,
                                     const QVariantList &playerIndexes)
    {
        emit sendTournamentCandidate(title,numberOfThrows,maxPlayers,gameMode,keyPoint,playerIndexes);
    }
    virtual void createPlayer(const QString &userName, const QString &email)
    {
        emit requestCreatePlayer(userName,email);
    }
    virtual void requestPlayerDetails()
    {
        emit requestPlayers();
    }

    virtual void handleSendGameModesRequest() const = 0;
    virtual void handleStatusRequest() = 0;
    virtual void addPoint(const int& value) = 0;

    virtual void startGame() = 0;
    virtual void stopGame() = 0;

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
                                 const int &maxPlayers,
                                 const int &gameMode,
                                 const int &keyPoint,
                                 const int &playersCount);
    void sendTournamentCandidate(const QString &title,
                                 const int &numberOfThrows,
                                 const int &maxPlayers,
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
    void requestStart();
    void requestStop();
    void requestPlayerScores();
    void setCurrentActiveTournament(const int &index);

protected:
    AbstractDataContext *dataContext() const
    {
        return _dataContext;
    }

    AbstractGameController *gameController() const
    {
        return _gameController;
    }

    DefaultControllerBuilderInterface *controllerBuilder() const
    {
        return _controllerBuilder;
    }

private:
    IControllerBuilder<AbstractGameController, int> *_controllerBuilder;
    AbstractDataContext *_dataContext = nullptr;
    AbstractGameController *_gameController= nullptr;

};


#endif // PROJECTDARTINTERFACE_H




