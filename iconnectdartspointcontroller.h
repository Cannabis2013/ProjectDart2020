#ifndef ICONNECTDARTSPOINTCONTROLLER_H
#define ICONNECTDARTSPOINTCONTROLLER_H

#include "abstractdartspointcontroller.h"
#include "AbstractApplicationInterface.h"
#include "abstractmodelsservice.h"
#include "abstractroutedartsbydisplayhint.h"

class IConnectDartsPointController
{
public:
    virtual void connectController(AbstractDartsController* controller,
                                   AbstractApplicationInterface* application,
                                   AbstractModelsService* modelsService,
                                   AbstractRouteDartsByDisplayHint* routeService) = 0;
};

#endif // ICONNECTDARTSPOINTCONTROLLER_H
