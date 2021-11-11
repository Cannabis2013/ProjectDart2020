#ifndef ICREATEDARTSCONTROLLER_H
#define ICREATEDARTSCONTROLLER_H
#include "DartsController/ControllerSLA/abstractdartscontroller.h"
#include "DartsControllerBuilder/DCBMetaServices/dcbmeta.h"
template<class TModelsContext>
class ICreateDartsController
{
public:
    virtual AbstractDartsController *create(TModelsContext *modelsContext) = 0;
};

#endif // ICREATEDARTSCONTROLLER_H
