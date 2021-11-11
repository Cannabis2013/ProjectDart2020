#ifndef CONNECTSERVICEPROVIDER_H
#define CONNECTSERVICEPROVIDER_H
#include "DartControllerContext/ConnectSLAs/iconnectcontroller.h"
class IConnectServicesProvider
{
public:
    virtual IConnectController *connectDC() const = 0;
};

#endif // CONNECTSERVICEPROVIDER_H
