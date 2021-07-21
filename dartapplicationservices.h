#ifndef DARTAPPLICATIONSERVICES_H
#define DARTAPPLICATIONSERVICES_H

#include <abstractdartscontrollerbuilder.h>
#include <abstractroutebyinputhint.h>
#include <abstractroutebydisplayhint.h>
#include <iconnectcontroller.h>
#include "iconnectservicesprovider.h"
#include "irouteservicesprovider.h"

class DartApplicationServices
{
public:
    AbstractModelsService *modelsService() const;
    AbstractGameController *gameController() const;
    AbstractDartsControllerBuilder *createDartsPointController() const;
    AbstractDartsControllerBuilder *createDartsScoreController() const;
    IConnectServicesProvider *connectServices() const;
    IRouteServicesProvider *routeServices() const;
protected:
    // Models services
    AbstractModelsService* _modelsService;
    // Controller service
    AbstractGameController *_gameController = nullptr;
    // Builders
    AbstractDartsControllerBuilder *_createDartsPointController;
    AbstractDartsControllerBuilder *_createDartsScoreController;
    // Connect darts controller services
    IConnectServicesProvider *_connectServices;
    IRouteServicesProvider *_routeServices;

};

#endif // DARTAPPLICATIONSERVICES_H
