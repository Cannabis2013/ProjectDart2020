#ifndef CONNECTDCBUILDER_H
#define CONNECTDCBUILDER_H
#include "iconnectdcbuilder.h"
class ConnectDCBuilder : public IConnectDCBuilder
{
public:
    static ConnectDCBuilder* createInstance()
    {
        return new ConnectDCBuilder;
    }
    void connectServices(AbstractDCBuilder *builderService,
                         AbstractApplicationInterface* applicationService) override
    {
        QObject::connect(builderService,&AbstractDCBuilder::sendController,
                         applicationService,&AbstractApplicationInterface::setDartsController);
    }
};
#endif // CONNECTROUTETODARTSSCOREBUILDER_H
