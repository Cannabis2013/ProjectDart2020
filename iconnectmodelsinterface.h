#ifndef ICONNECTMODELSINTERFACE_H
#define ICONNECTMODELSINTERFACE_H

#include "abstractmodelsservice.h"
#include "AbstractApplicationInterface.h"

class IConnectModelsInterface
{
public:
    virtual void connectModelsInterface(AbstractApplicationInterface* application,
                                        AbstractModelsService* modelsService) = 0;
};

#endif // ICONNECTMODELSINTERFACE_H
