#ifndef CONNECTROUTEBYTOURNAMENTHINT_H
#define CONNECTROUTEBYTOURNAMENTHINT_H

#include "iconnectroutetodartsbuilder.h"
#include "qobject.h"

class ConnectDartsPointBuilder : public
        IConnectRouteToDartsBuilder
{
public:
    static ConnectDartsPointBuilder* createInstance()
    {
        return new ConnectDartsPointBuilder;
    }
    void connectServices(AbstractRouteByInputHint *routeByInputHint,
                         AbstractDartsControllerBuilder *builderService,
                         AbstractApplicationInterface* applicationService) override
    {
        QObject::connect(routeByInputHint,&AbstractRouteByInputHint::requestBuildDartsPointController,
                         builderService,&AbstractDartsControllerBuilder::buildDartsController);
        QObject::connect(builderService,&AbstractDartsControllerBuilder::sendController,
                         applicationService,&AbstractApplicationInterface::setDartsPointController);

    }
};


#endif // CONNECTROUTEBYTOURNAMENTHINT_H
