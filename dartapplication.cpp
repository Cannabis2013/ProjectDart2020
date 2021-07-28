#include "dartapplication.h"

void DartApplication::createDartsTournamentFromJson(const QByteArray &json)
{
    auto future = playerModelsContext()->playerModels(json);
    runAsync<Models>([=](){
        _dartsModelsContext->addDartsTournament(json,future.result());
    },future);
}

void DartApplication::handleSendGameModesRequest() const
{
    QStringList resultingList = {"FirstToPost","RoundLimit","Circular"};
    emit sendGameModes(resultingList);
}

void DartApplication::setDartsPointController(AbstractDartsController *controller)
{
    delete _gameController;
    _gameController = controller;
    connectServices()->connectDartsPointController()->connectController(controller,this,_dartsModelsContext,
                                                                        routeServices()->routeByDisplayHint());
    emit requestWakeUp();
}

void DartApplication::setDartsScoreController(AbstractDartsController *controller)
{
    delete _gameController;
    _gameController = controller;
    connectServices()->connectDartsScoreController()
            ->connectController(controller,this,_dartsModelsContext,routeServices()->routeByDisplayHint());
    emit requestWakeUp();
}

void DartApplication::clearGameController()
{
    _gameController->disconnect();
    delete _gameController;
    _gameController = nullptr;
}

template<typename T>
void DartApplication::runAsync(Func funct, const QFuture<T> &future)
{
    auto watcher = new QFutureWatcher<T>();
    connect(watcher,&QFutureWatcherBase::finished, [=](){
        funct();
        delete watcher;
    });
    watcher->setFuture(future);
}
