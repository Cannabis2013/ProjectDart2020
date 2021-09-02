#ifndef CONNECTDCBUILDER_H
#define CONNECTDCBUILDER_H

#include "iconnectroutetodartsbuilder.h"


class ConnectDCBuilder : public IConnectRouteToDartsBuilder
{
public:
    static ConnectDCBuilder* createInstance()
    {
        return new ConnectDCBuilder;
    }
    void connectServices(AbstractRouteByInputHint *routeByInputHint,
                         AbstractDCBuilder *builderService,
                         AbstractApplicationInterface* applicationService) override
    {
        QObject::connect(routeByInputHint,&AbstractRouteByInputHint::requestBuildDartsScoreController,
                         builderService,&AbstractDCBuilder::buildPointBasedController);
        QObject::connect(builderService,&AbstractDCBuilder::sendController,
                         applicationService,&AbstractApplicationInterface::setDartsController);
    }
};

#endif // CONNECTROUTETODARTSSCOREBUILDER_H
