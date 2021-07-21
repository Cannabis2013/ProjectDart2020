#include "dartapplication.h"

void DartApplication::handleSendGameModesRequest() const
{
    QStringList resultingList = {"FirstToPost","RoundLimit","Circular"};
    emit sendGameModes(resultingList);
}

void DartApplication::createDartsTournamentValues()
{
    emit requestCurrentTournamentId();
}

void DartApplication::setDartsPointController(AbstractDartsController *controller)
{
    delete _gameController;
    _gameController = controller;
    connectServices()->connectDartsPointController()->connectController(controller,this,_modelsService,
                                                                        routeServices()->routeByDisplayHint());
    emit requestWakeUp();
}

void DartApplication::setDartsScoreController(AbstractDartsController *controller)
{
    delete _gameController;
    _gameController = controller;

    connectServices()->connectDartsScoreController()->connectController(controller,this,_modelsService,
                                                                        routeServices()->routeByDisplayHint());
    emit requestWakeUp();
}

void DartApplication::clearGameController()
{
    _gameController->disconnect();
    delete _gameController;
    _gameController = nullptr;
}
