#ifndef ICONNECTDARTSMODELSCONTEXT_H
#define ICONNECTDARTSMODELSCONTEXT_H

#include "DartsModelsContext/abstractdartsmodelscontext.h"
#include "AbstractApplicationInterface.h"

#include <abstractdcbuilder.h>

class IConnectDartsModelsContext
{
public:
    virtual void connect(AbstractApplicationInterface* application,
                         AbstractDartsModelsContext* modelsService,
                         AbstractDCBuilder *dcBuilder) = 0;
};

#endif // ICONNECTDARTSMODELSCONTEXT_H
