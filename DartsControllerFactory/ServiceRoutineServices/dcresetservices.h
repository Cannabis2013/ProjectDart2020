#ifndef DCRESETSERVICES_H
#define DCRESETSERVICES_H
#include "ServiceRoutineSLAs/idcresetservices.h"
class DCServices;
class DCResetServices : public IDCResetServices
{
public:
    DCResetServices(DCServices *services):
        _services(services){}
    virtual void reset() override;
private:
    DCServices *_services;
};

#endif // DCRESETSERVICES_H
