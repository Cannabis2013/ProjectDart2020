#ifndef CONNECTDARTSSCOREBUILDER_H
#define CONNECTDARTSSCOREBUILDER_H

#include "iconnectroutetodartsbuilder.h"


class ConnectDartsScoreBuilder : public IConnectRouteToDartsBuilder
{
public:
    static ConnectDartsScoreBuilder* createInstance()
    {
        return new ConnectDartsScoreBuilder;
    }
    void connectServices(AbstractRouteByInputHint *routeByInputHint,
                         AbstractDartsControllerBuilder *builderService,
                         AbstractApplicationInterface* applicationService) override
    {
        QObject::connect(routeByInputHint,&AbstractRouteByInputHint::requestBuildDartsScoreController,
                         builderService,&AbstractDartsControllerBuilder::buildDartsController);
        QObject::connect(builderService,&AbstractDartsControllerBuilder::sendController,
                         applicationService,&AbstractApplicationInterface::setDartsScoreController);
    }
};

#endif // CONNECTROUTETODARTSSCOREBUILDER_H
