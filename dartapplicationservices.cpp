#include "dartapplicationservices.h"

AbstractDartsModelsContext *DartApplicationServices::modelsService() const
{
    return _dartsModelsContext;
}

AbstractGameController *DartApplicationServices::gameController() const
{
    return _gameController;
}

AbstractDCBuilder *DartApplicationServices::dcBuilder() const
{
    return _dcBuilder;
}

IConnectServicesProvider *DartApplicationServices::connectServices() const
{
    return _connectServices;
}

IRouteServicesProvider *DartApplicationServices::routeServices() const
{
    return _routeServices;
}

IPlayerModelsContext *DartApplicationServices::playerModelsContext() const
{
    return _playerModelsContext;
}

void DartApplicationServices::setPlayerModelsContext(IPlayerModelsContext *newPlayerModelsContext)
{
    _playerModelsContext = newPlayerModelsContext;
}
