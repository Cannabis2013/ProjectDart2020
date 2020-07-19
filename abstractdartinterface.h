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

    AbstractDartInterface(AbstractDataContext *dataContext, AbstractGameController *gameController, DefaultControllerBuilderInterface *_builder)
    {
        _dataContext = dataContext;
        _gameController = gameController;

        connect(this,&AbstractDartInterface::requestTournaments,_dataContext,&AbstractDataContext::sendRequestedTournaments);
        connect(_dataContext,&AbstractDataContext::sendTournament,this,&AbstractDartInterface::sendRequestedTournament);

        connect(this,&AbstractDartInterface::setCurrentActiveTournament,_dataContext,&AbstractDataContext::handleSetCurrentTournament);

        connect(_dataContext,&AbstractDataContext::sendInitialControllerValues,_gameController,&AbstractGameController::initializeController);
        connect(_gameController,&AbstractGameController::requestInitialIndexes,_dataContext,&AbstractDataContext::handleInitialIndexesRequest);
        connect(_dataContext,&AbstractDataContext::sendInitialControllerIndexes,_gameController,&AbstractGameController::initializeIndexes);

        connect(_gameController,&AbstractGameController::sendStatus,this,&AbstractDartInterface::sendStatus);
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

    virtual void gameModes() const = 0;
    virtual void handleStatusRequest() = 0;
    virtual void addPoint(const int& value) = 0;

    virtual void startGame() = 0;
    virtual void stopGame() = 0;

protected slots:
    virtual void forwardScoreFromDataContext(const QUuid &player, const int &score) = 0;

signals:
    virtual void requestTournaments();
    void sendPlayerDetails(const QString &firstName, const QString &lastName, const QString &mail);
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

    // IStatusInterface interface
    void recieveStatus(const int &status, const QVariantList &args) override
    {
    }

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




