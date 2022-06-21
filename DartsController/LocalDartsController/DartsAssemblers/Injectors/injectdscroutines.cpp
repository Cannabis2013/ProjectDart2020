#include "injectdscroutines.h"
#include <DartsController/LocalDartsController/Controller/dartscontroller.h>
#include <DartsController/LocalDartsController/Init/dcinitialize.h>
#include <DartsController/LocalDartsController/Routines/dcaddinput.h>
#include <DartsController/LocalDartsController/Routines/dccreatewinnerreport.h>
#include <DartsController/LocalDartsController/Routines/dcgetscoresasjson.h>
#include <DartsController/LocalDartsController/Routines/dcgetturnvaluesasjson.h>
#include <DartsController/LocalDartsController/Routines/dcredoturn.h>
#include <DartsController/LocalDartsController/Routines/dcresetservices.h>
#include <DartsController/LocalDartsController/Routines/dcundoturn.h>

void InjectDSCRoutines::inject(DartsController *controller)
{
    controller->setInitializer(new DCInitialize(controller));
    controller->setResetServices(new DCResetServices(controller));
    controller->setUpdateModelsContext(new DCAddInput);
    controller->setCreateWinnerReport(new DCCreateWinnerReport(controller));
    controller->setGetTurnValuesAsJson(new DCGetTurnValuesAsJson(controller));
    controller->setGetScoresAsJson(new DCGetScoresAsJson(controller));
    controller->setUndoTurn(new DCUndoTurn(controller));
    controller->setRedoTurn(new DCRedoTurn(controller));
}
