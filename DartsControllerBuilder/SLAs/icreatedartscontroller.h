#ifndef ICREATEDARTSCONTROLLER_H
#define ICREATEDARTSCONTROLLER_H
#include "DartsController/ControllerSLA/abstractdartscontroller.h"
#include "DartsControllerBuilder/DCBMetaServices/dcbmeta.h"
class ICreateDartsController
{
public:
    virtual AbstractDartsController *create(const DCBMeta &meta) = 0;
};

#endif // ICREATEDARTSCONTROLLER_H
