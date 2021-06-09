#ifndef CONNECTROUTETODARTSSCOREBUILDER_H
#define CONNECTROUTETODARTSSCOREBUILDER_H

#include "iconnectroutetodartsbuilder.h"


class ConnectRouteToDartsScoreBuilder : public IConnectRouteToDartsBuilder
{
public:
    static ConnectRouteToDartsScoreBuilder* createInstance()
    {
        return new ConnectRouteToDartsScoreBuilder;
    }
    void connectServices(AbstractRouteByInputHint *routeByInputHint,
                         AbstractDartsControllerBuilder *builderService,
                         AbstractRouteByDisplayHint* routeByDisplayHint) override
    {
        QObject::connect(routeByInputHint,&AbstractRouteByInputHint::requestBuildDartsScoreController,
                         builderService,&AbstractDartsControllerBuilder::buildDartsController);
        QObject::connect(builderService,&AbstractDartsControllerBuilder::sendController,
                         routeByDisplayHint,&AbstractRouteByDisplayHint::processDartsController);
    }
};

#endif // CONNECTROUTETODARTSSCOREBUILDER_H
