#ifndef DARTAPPLICATIONSLAS_H
#define DARTAPPLICATIONSLAS_H

#include "DartsControllerBuilder/SLAs/abstractdcbuilder.h"
#include "DartApplication/RouteSLAs/abstractroutebyhint.h"
#include "DartControllerContext/ConnectSLAs/iconnectcontroller.h"
#include "ServicesProviderContext/SPConnectSLAs//iconnectservicesprovider.h"
#include "DartApplication/RouteSLAs/irouteservicesprovider.h"
#include "PlayerModelsContext/SLAs/iplayermodelscontext.h"

class DartApplicationSLAs : public AbstractApplicationInterface
{
public:
    AbstractDartsModelsContext *modelsService() const;
    AbstractGameController *gameController() const;
    AbstractDCBuilder *dcBuilder() const;
    IConnectServicesProvider *connectServices() const;
    IRouteServicesProvider *routeServices() const;
    IPlayerModelsContext *playerModelsContext() const;
    void setPlayerModelsContext(IPlayerModelsContext *service);
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
