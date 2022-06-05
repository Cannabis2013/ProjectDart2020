#include "injectdscroutines.h"
#include <DartsController/Controller/dartscontroller.h>
#include <LocalDartsController/Init/dcinitialize.h>
#include <LocalDartsController/Routines/dcaddinput.h>
#include <LocalDartsController/Routines/dccreatewinnerreport.h>
#include <LocalDartsController/Routines/dcgetscoresasjson.h>
#include <LocalDartsController/Routines/dcgetturnvaluesasjson.h>
#include <LocalDartsController/Routines/dcredoturn.h>
#include <LocalDartsController/Routines/dcresetservices.h>
#include <LocalDartsController/Routines/dcundoturn.h>

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
