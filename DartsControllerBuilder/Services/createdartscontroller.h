#ifndef CREATEDARTSCONTROLLER_H
#define CREATEDARTSCONTROLLER_H
#include "DartsController/Controller/dartscontroller.h"
#include "DartsController/DSCServices/dscinputbuilder.h"
#include "DartsControllerBuilder/DCBMetaSLAs/icreatedcmetainfo.h"
#include "DartsController/DSController/createdsc.h"
#include "DartsController/DPController/createdpc.h"
class CreateDartsController
{
public:
    AbstractDartsController *createDartsPointController()
    {
        return CreateDSC::create();
    }
    AbstractDartsController *createDartsScoreController()
    {
        return CreateDPC::create();
    }
};
#endif // BUILDDARTSSCORECONTROLLER_H
