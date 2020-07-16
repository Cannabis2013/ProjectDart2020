#ifndef PROJECTDARTINTERFACE_H
#define PROJECTDARTINTERFACE_H

#include <QtCore>

#include <idatacontext.h>
#include <abstractcontrollerinterface.h>
#include <iplayercontext.h>
#include <idatamodelbuilder.h>
#include "iplayermodel.h"
#include "iplayerbuildercontext.h"
#include "IControllerBuilder.h"


/*
 * This is the interface you will pass to the visual QML layer
 * Make sure that methods are marked with the Q_INVOKABLE macro and return types which are accepted by the QML engine
 *
 */

typedef IPlayerModel<QUuid,QString> DefaultModelInterface;
typedef IPlayerBuilderParameters<QString> DefaultParameters;
typedef IDataModelBuilder<DefaultModelInterface,DefaultParameters,IPlayerBuilderConfiguration> DefaultPlayerBuilder;
typedef IDataContext<QUuid,QList<QUuid>,QString,ITournamentBuilder> DefaultDataInterface;
typedef IPlayerContext<QUuid,QList<QUuid>,QString, DefaultPlayerBuilder> PlayerContextInterface;
typedef IController<QUuid,QString, DefaultDataInterface> GameControllerInterface;


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
    virtual void assignPlayer(const QString &player, const QString &tournament) = 0;
    virtual int tournamentsCount() = 0;
    virtual QString tournamentIDFromIndex(const int &index) = 0;
    virtual int tournamentMaxPlayers(const QString &id) = 0;
    virtual int tournamentLegsCount(const QString &id) = 0;
    virtual int tournamentPlayersCount(const QString &id) = 0;
    virtual QString tournamentTitle(const QString &id) = 0;
    virtual int tournamentKeyPoint(const QString &id) = 0;
    virtual int pointValue(const QString &point) const = 0;
    virtual int pointValue(const QString &tournament, const QString &player, const int &roundIndex, const int &legIndex) const = 0;
    virtual QStringList gameModes() const = 0;
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
    virtual int addPoint(const int& value) = 0;
    virtual int startGame() = 0;
    virtual int stopGame() = 0;
    virtual int undoTurn() = 0;
    virtual int redoTurn() = 0;
    virtual bool undoPossible() = 0;
    virtual bool redoPossible() = 0;
    virtual int gameStatus() = 0;
    virtual int score(const QString &player) = 0;


    IControllerBuilder<AbstractControllerInterface, int> *controllerBuilder() const
    {
        return _controllerBuilder;
    }
    void setControllerBuilder(IControllerBuilder<AbstractControllerInterface, int> *controllerBuilder)
    {
        _controllerBuilder = controllerBuilder;
    }

    DefaultDataInterface *dataContext() const
    {
        return _dataContext;
    }
    void setDataContext(DefaultDataInterface *dataContext)
    {
        _dataContext = dataContext;
    }

    PlayerContextInterface *playerContext() const
    {
        return _playerContext;
    }
    void setPlayerContext(PlayerContextInterface *playerContext)
    {
        _playerContext = playerContext;
    }

    AbstractControllerInterface *gameController() const
    {
        return _gameController;
    }
    void setGameController(AbstractControllerInterface *gameController)
    {
        _gameController = gameController;

        connect(_gameController,&AbstractControllerInterface::stateChanged,this,&AbstractDartInterface::handleStateChange);
        connect(_gameController,&AbstractControllerInterface::sendControllerStatus,this,&AbstractDartInterface::sendStatus);
    }
public slots:
    virtual void createTournament(const QString &title,
                                     const int &numberOfThrows,
                                     const int &maxPlayers,
                                     const int &gameMode,
                                     const int &keyPoint) = 0;
    virtual void createPlayer(const QString &firstName, const QString &lastName, const QString &email) = 0;
    virtual void requestPlayerDetails() = 0;
    virtual void requestTournaments() = 0;
    virtual void handleScoreBoardRequest() = 0;
    virtual void setCurrentActiveTournament(const int &index) = 0;

protected slots:
    virtual void handleStateChange() = 0;

signals:
    void sendPlayerDetails(const QString &firstName, const QString &lastName, const QString &mail);
    void sendStatus(const int &status);
    void sendPlayerScore(const QString &playerName, const int &score);
    void sendAssignedPlayerName(const QString &playerName);
    void sendRequestetTournament(const QString &title,
                                 const int &numberOfThrows,
                                 const int &maxPlayers,
                                 const int &gameMode,
                                 const int &keyPoint,
                                 const int &playersCount);
    void sendCurrentTournamentKeyPoint(const int &point);
    void sendInformalControllerValues(const int &roundIndex,
                                      const QString &playerName,
                                      const bool &undoAvailable,
                                      const bool &redoAvailable);

private:
    IControllerBuilder<AbstractControllerInterface, int> *_controllerBuilder;
    DefaultDataInterface *_dataContext = nullptr;
    PlayerContextInterface *_playerContext= nullptr;
    AbstractControllerInterface *_gameController= nullptr;

};

#endif // PROJECTDARTINTERFACE_H




