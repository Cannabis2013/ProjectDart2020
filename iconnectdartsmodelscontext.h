#ifndef ICONNECTDARTSMODELSCONTEXT_H
#define ICONNECTDARTSMODELSCONTEXT_H

#include "abstractdartsmodelscontext.h"
#include "AbstractApplicationInterface.h"

class IConnectDartsModelsContext
{
public:
    virtual void connect(AbstractApplicationInterface* application,
                         AbstractDartsModelsContext* modelsService) = 0;
};

#endif // ICONNECTDARTSMODELSCONTEXT_H
