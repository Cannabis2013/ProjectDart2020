#ifndef ICONNECTDCBUILDER_H
#define ICONNECTDCBUILDER_H
#include <abstractdcbuilder.h>
class IConnectDCBuilder
{
public:
    virtual void connectServices(AbstractDCBuilder *builderService,
                                 AbstractApplicationInterface *applicationService) = 0;
};
#endif // ICONNECTDCBUILDER_H
