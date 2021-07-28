#ifndef ICONNECTPLAYERMODELSCONTEXT_H
#define ICONNECTPLAYERMODELSCONTEXT_H
#include "AbstractApplicationInterface.h"
#include "iplayermodelscontext.h"
class IConnectPlayerModelsContext
{
public:
    virtual void connectServices(AbstractApplicationInterface *application,
                                 IPlayerModelsContext *modelsContext) = 0;
};

#endif // ICONNECTPLAYERMODELSCONTEXT_H
