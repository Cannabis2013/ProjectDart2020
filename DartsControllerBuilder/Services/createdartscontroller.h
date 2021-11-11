#ifndef CREATEDARTSCONTROLLER_H
#define CREATEDARTSCONTROLLER_H
#include "DartsController/Controller/dartscontroller.h"
#include "DartsController/DSCServices/dscinputbuilder.h"
#include "DartsControllerBuilder/DCBMetaSLAs/icreatedcmetainfo.h"
#include "DartsControllerBuilder/SLAs/icreatedartscontroller.h"
#include "DartsController/DSController/createdsc.h"
#include "DartsController/DPController/createdpc.h"
class CreateDartsController
{
public:
    AbstractDartsController *createDartsPointController(AbstractDartsContext *modelsContext = nullptr)
    {
        if(modelsContext != nullptr)
            return _createDPC->create(modelsContext);
        throw "Modelscontext not injected";
    }
    AbstractDartsController *createDartsScoreController(AbstractDartsContext *modelsContext = nullptr)
    {
        if(modelsContext != nullptr)
            return _createDSC->create(modelsContext);
        throw "Modelscontext not injected";
    }
private:
    ICreateDartsController<AbstractDartsContext> *_createDPC = new CreateDSC;
    ICreateDartsController<AbstractDartsContext> *_createDSC = new CreateDPC;
};
#endif // BUILDDARTSSCORECONTROLLER_H
