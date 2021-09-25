#ifndef ICONNECTDARTSMODELSCONTEXT_H
#define ICONNECTDARTSMODELSCONTEXT_H

#include "DartsModelsContext/SLAs/abstractdartsmodelscontext.h"
#include "DartApplication/SLAs/AbstractApplicationInterface.h"

#include "DartsControllerBuilder/SLAs/abstractdcbuilder.h"

class IConnectDartsModelsContext
{
public:
    virtual void connect(AbstractApplicationInterface* application,
                         AbstractDartsModelsContext* modelsService,
                         AbstractDCBuilder *dcBuilder) = 0;
};

#endif // ICONNECTDARTSMODELSCONTEXT_H
