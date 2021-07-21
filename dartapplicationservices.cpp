#include "dartapplicationservices.h"

AbstractModelsService *DartApplicationServices::modelsService() const
{
    return _modelsService;
}

AbstractGameController *DartApplicationServices::gameController() const
{
    return _gameController;
}

AbstractDartsControllerBuilder *DartApplicationServices::createDartsPointController() const
{
    return _createDartsPointController;
}

AbstractDartsControllerBuilder *DartApplicationServices::createDartsScoreController() const
{
    return _createDartsScoreController;
}

IConnectServicesProvider *DartApplicationServices::connectServices() const
{
    return _connectServices;
}

IRouteServicesProvider *DartApplicationServices::routeServices() const
{
    return _routeServices;
}
