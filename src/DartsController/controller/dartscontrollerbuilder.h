#ifndef DARTSCONTROLLERS_H
#define DARTSCONTROLLERS_H

#include "src/DartsController/controller/dartscontroller.h"

class DartsJsonReport;

class DartsControllerBuilder {
public:
        DartsController* build();
};

#endif // DARTSCONTROLLERS_H
