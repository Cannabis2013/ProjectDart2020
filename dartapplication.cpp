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
    _connectDartsPointController->connectController(controller,this,_modelsService,_routeDartsControllerByDisplayHint);
    emit requestWakeUp();
}

void DartApplication::setDartsScoreController(AbstractDartsController *controller)
{
    delete _gameController;
    _gameController = controller;
    _connectDartsScoreController->connectController(controller,this,_modelsService,_routeDartsControllerByDisplayHint);
    emit requestWakeUp();
}

void DartApplication::clearGameController()
{
    _gameController->disconnect();
    delete _gameController;
    _gameController = nullptr;
}

AbstractGameController *DartApplication::gameController() const
{
    return _gameController;
}
