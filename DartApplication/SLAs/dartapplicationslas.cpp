#include "dartapplicationslas.h"

AbstractDartsModelsContext *DartApplicationSLAs::modelsService() const
{
    return _dartsModelsContext;
}

AbstractGameController *DartApplicationSLAs::gameController() const
{
    return _gameController;
}

AbstractDCBuilder *DartApplicationSLAs::dcBuilder() const
{
    return _dcBuilder;
}

IConnectServicesProvider *DartApplicationSLAs::connectServices() const
{
    return _connectServices;
}

IRouteServicesProvider *DartApplicationSLAs::routeServices() const
{
    return _routeServices;
}

IPlayerModelsContext *DartApplicationSLAs::playerModelsContext() const
{
    return _playerModelsContext;
}

void DartApplicationSLAs::setPlayerModelsContext(IPlayerModelsContext *newPlayerModelsContext)
{
    _playerModelsContext = newPlayerModelsContext;
}
