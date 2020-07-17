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
typedef IDataContext<QUuid,QList<QUuid>,QString,ITournamentBuilder,DefaultPlayerBuilder> DefaultDataInterface;
typedef IController<QUuid,QString> GameControllerInterface;


class AbstractDartInterface : public QObject
{
    Q_OBJECT
public:

    /*
     * Tournament:
     *  - Create/read/delete/edit tournament
     *  -
     */

    virtual void createInitialModels() const = 0;
    virtual void assignPlayer(const QUuid &player, const QUuid &tournament) = 0;
    virtual int tournamentsCount() = 0;
    virtual QString tournamentIDFromIndex(const int &index) = 0;
    virtual int tournamentMaxPlayers(const QString &id) = 0;
    virtual int tournamentLegsCount(const QString &id) = 0;
    virtual int tournamentPlayersCount(const QString &id) = 0;
    virtual QString tournamentTitle(const QString &id) = 0;
    virtual int tournamentKeyPoint(const QString &id) = 0;
    virtual int pointValue(const QString &point) const = 0;
    virtual int pointValue(const QString &tournament, const QString &player, const int &roundIndex, const int &legIndex) const = 0;
    virtual int playersCount() = 0;
    virtual QString assignedPlayerIDfromIndex(const QString &tournamentID, const int &index) = 0;
    virtual QString playerIDFromIndex(const int &index) = 0;
    virtual QString playerIDFromFullName(const QString &name) = 0;
    virtual QString playerFullName(const QString &player) = 0;
    virtual QString playerFirstName(const QString &player) = 0;
    virtual QString playerLastName(const QString &player) = 0;
    virtual QString playerEmail(const QString &player) = 0;
    virtual QString currentActiveTournamentID() = 0;
    virtual QString currentActivePlayerFullName() = 0;
    virtual QString currentPlayerPoint(const int &hint) = 0;
    virtual int currentGameRoundIndex() = 0;
    virtual int currentGameSetIndex() = 0;
    virtual int currentGameLegIndex() = 0;
    virtual int undoTurn() = 0;
    virtual int redoTurn() = 0;
    virtual bool undoPossible() = 0;
    virtual bool redoPossible() = 0;
    virtual int score(const QString &player) = 0;


    IControllerBuilder<AbstractGameController, int> *controllerBuilder() const
    {
        return _controllerBuilder;
    }
    void setControllerBuilder(IControllerBuilder<AbstractGameController, int> *controllerBuilder)
    {
        _controllerBuilder = controllerBuilder;
    }

    AbstractDataContext *dataContext() const
    {
        return _dataContext;
    }
    void setDataContext(AbstractDataContext *dataContext)
    {
        _dataContext = dataContext;

        connect(_dataContext,&AbstractDataContext::sendPlayerScore,this,&AbstractDartInterface::sendPlayerScore);
        connect(_gameController,&AbstractGameController::sendCurrentTournament,_dataContext,&AbstractDataContext::sendPlayerScores);
        connect(_dataContext,&AbstractDataContext::sendCurrentTournamentKeyPoint,this,&AbstractDartInterface::sendCurrentTournamentKeyPoint);
        connect(_dataContext,&AbstractDataContext::sendAssignedPlayerName,this,&AbstractDartInterface::sendAssignedPlayerName);
    }

    AbstractGameController *gameController() const
    {
        return _gameController;
    }
    void setGameController(AbstractGameController *gameController)
    {
        _gameController = gameController;

        connect(_gameController,&AbstractGameController::sendStatus,this,&AbstractDartInterface::handleGameStatusRecieved);
        connect(this,&AbstractDartInterface::requestStart,_gameController,&AbstractGameController::start);
        connect(this,&AbstractDartInterface::requestStop,_gameController,&AbstractGameController::stop);
        connect(this,&AbstractDartInterface::requestPlayerDetails,_gameController,&AbstractGameController::handleCurrentTournamentRequest);
    }
public slots:
    virtual void createTournament(const QString &title,
                                     const int &numberOfThrows,
                                     const int &maxPlayers,
                                     const int &gameMode,
                                     const int &keyPoint) = 0;
    virtual void createPlayer(const QString &firstName, const QString &lastName, const QString &email) = 0;
    virtual void assignPlayers(const QVariantList &list, const QString &tournament) = 0;
    virtual void requestPlayerDetails() = 0;
    virtual void requestTournaments() = 0;

    virtual void setCurrentActiveTournament(const int &index) = 0;
    virtual void gameModes() const = 0;
    virtual void handleStatusRequest() = 0;
    virtual int addPoint(const int& value) = 0;

    virtual int startGame() = 0;
    virtual int stopGame() = 0;

protected slots:
    virtual void handleGameStatusRecieved(const int &status) = 0;
    virtual void forwardScoreFromDataContext(const QUuid &player, const int &score) = 0;

signals:
    void sendPlayerDetails(const QString &firstName, const QString &lastName, const QString &mail);
    void sendStatus(const int &status, const QVariantList &arguments);
    void sendPlayerScore(const QString &playerName, const int &score);
    void sendAssignedPlayerName(const QString &playerName);
    void sendCurrentTournamentKeyPoint(const int &point);
    void sendRequestedTournament(const QString &title,
                                 const int &numberOfThrows,
                                 const int &maxPlayers,
                                 const int &gameMode,
                                 const int &keyPoint,
                                 const int &playersCount);
    void sendInformalControllerValues(const int &roundIndex,
                                      const QString &playerName,
                                      const bool &undoAvailable,
                                      const bool &redoAvailable);
    void sendGameModes(const QStringList &modes) const;
    void stateChanged();
    void sendInitialControllerValues(const QUuid &tournament,const int &keyPoint, const int &numberOfThrows, QList<QUuid> assignedPlayers);
    void sendInitialControllerIndexes(const int &roundIndex,
                                    const int &setIndex,
                                    const int &throwIndex,
                                    const int &turnIndex,
                                    const int &totalTurns);

    void requestStart();
    void requestStop();

    virtual void requestPlayerScores();

private:
    IControllerBuilder<AbstractGameController, int> *_controllerBuilder;
    AbstractDataContext *_dataContext = nullptr;
    AbstractGameController *_gameController= nullptr;

};

#endif // PROJECTDARTINTERFACE_H




