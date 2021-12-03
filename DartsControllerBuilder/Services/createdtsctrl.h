#ifndef CREATEDTSCTRL_H
#define CREATEDTSCTRL_H
#include "DartsController/Controller/dartscontroller.h"
#include "DartsController/DSCServices/dscinputbuilder.h"
#include "DartsControllerBuilder/DCBMetaSLAs/icreatedcmetainfo.h"
#include "DartsController/DSController/createdsc.h"
#include "DartsController/DPController/createdpc.h"
class CreateDtsCtrl
{
public:
    DartsController *pointCtrl()
    {
        return CreateDPC::create();
    }
    DartsController *scoreCtrl()
    {
        return CreateDSC::create();
    }
};
#endif // BUILDDARTSSCORECONTROLLER_H
