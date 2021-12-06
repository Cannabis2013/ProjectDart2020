#ifndef CREATEDTSCTRL_H
#define CREATEDTSCTRL_H
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
