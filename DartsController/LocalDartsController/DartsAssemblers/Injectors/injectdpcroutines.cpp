#include "injectdpcroutines.h"

#include <DartsController/LocalDartsController/Controller/dartscontroller.h>
#include <DartsController/LocalDartsController/Routines/dcaddinput.h>
#include <DartsController/LocalDartsController/Routines/dccreatewinnerreport.h>
#include <DartsController/LocalDartsController/Routines/dcgetscoresasjson.h>
#include <DartsController/LocalDartsController/Routines/dcgetturnvaluesasjson.h>
#include <DartsController/LocalDartsController/Routines/dcredoturn.h>
#include <DartsController/LocalDartsController/Routines/dcresetservices.h>
#include <DartsController/LocalDartsController/Routines/dcundoturn.h>
#include <DartsController/LocalDartsController/Init/dcinitialize.h>

void InjectDPCRoutines::inject(DartsController *controller)
{
    controller->setUpdateModelsContext(new DCAddInput);
    controller->setInitializer(new DCInitialize(controller));
    controller->setResetServices(new DCResetServices(controller));
    controller->setCreateWinnerReport(new DCCreateWinnerReport(controller));
    controller->setGetTurnValuesAsJson(new DCGetTurnValuesAsJson(controller));
    controller->setGetScoresAsJson(new DCGetScoresAsJson(controller));
    controller->setUndoTurn(new DCUndoTurn(controller));
    controller->setRedoTurn(new DCRedoTurn(controller));
}
