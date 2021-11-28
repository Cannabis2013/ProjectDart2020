#ifndef CREATEDTSCTRL_H
#define CREATEDTSCTRL_H
#include "DartsController/Controller/dartsctrl.h"
#include "DartsController/DSCServices/dscinputbuilder.h"
#include "DartsControllerBuilder/DCBMetaSLAs/icreatedcmetainfo.h"
#include "DartsController/DSController/createdsc.h"
#include "DartsController/DPController/createdpc.h"
class CreateDtsCtrl
{
public:
    DartsCtrl *pointCtrl()
    {
        return CreateDPC::create();
    }
    DartsCtrl *scoreCtrl()
    {
        return CreateDSC::create();
    }
};
#endif // BUILDDARTSSCORECONTROLLER_H
