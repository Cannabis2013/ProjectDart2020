#ifndef ICONNECTDARTSPOINTCONTROLLER_H
#define ICONNECTDARTSPOINTCONTROLLER_H

#include "abstractdartspointcontroller.h"
#include "AbstractApplicationInterface.h"
#include "abstractmodelsservice.h"

class IConnectDartsPointController
{
public:
    virtual void connectController(AbstractDartsController* controller,
                                   AbstractApplicationInterface* application,
                                   AbstractModelsService* modelsService) = 0;
};

#endif // ICONNECTDARTSPOINTCONTROLLER_H
