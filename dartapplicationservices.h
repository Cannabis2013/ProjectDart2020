#ifndef DARTAPPLICATIONSERVICES_H
#define DARTAPPLICATIONSERVICES_H

#include <abstractdcbuilder.h>
#include <abstractroutebydisplayhint.h>
#include <iconnectcontroller.h>
#include "iconnectservicesprovider.h"
#include "irouteservicesprovider.h"
#include "iplayermodelscontext.h"

class DartApplicationServices : public AbstractApplicationInterface
{
public:
    AbstractDartsModelsContext *modelsService() const;
    AbstractGameController *gameController() const;
    AbstractDCBuilder *dcBuilder() const;
    IConnectServicesProvider *connectServices() const;
    IRouteServicesProvider *routeServices() const;
    IPlayerModelsContext *playerModelsContext() const;
    void setPlayerModelsContext(IPlayerModelsContext *newPlayerModelsContext);
protected:
    // Darts models context
    AbstractDartsModelsContext* _dartsModelsContext;
    // Player models context
    IPlayerModelsContext *_playerModelsContext;
    // Controller service
    AbstractGameController *_gameController = nullptr;
    // Builders
    AbstractDCBuilder *_createDartsPointController;
    AbstractDCBuilder *_dcBuilder;
    // Connect darts controller services
    IConnectServicesProvider *_connectServices;
    // Route services
    IRouteServicesProvider *_routeServices;
};

#endif // DARTAPPLICATIONSERVICES_H
