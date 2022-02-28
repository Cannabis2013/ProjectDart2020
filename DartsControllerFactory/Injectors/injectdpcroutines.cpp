#include "injectdpcroutines.h"
#include "Routines/dcaddinput.h"
#include "Init/dcinitialize.h"
#include "Routines/dccreatewinnerreport.h"
#include "Routines/dcresetservices.h"
#include "Routines/dcgetturnvaluesasjson.h"
#include "Routines/dcgetscoresasjson.h"
#include "Routines/dcundoturn.h"
#include "Routines/dcredoturn.h"
#include <Controller/dartscontroller.h>

void InjectDPCRoutines::inject(DartsController *controller)
{
    controller->setUpdateModelsContext(new DCAddInput(controller));
    controller->setInitializer(new DCInitialize(controller));
    controller->setResetServices(new DCResetServices(controller));
    controller->setCreateWinnerReport(new DCCreateWinnerReport(controller));
    controller->setGetTurnValuesAsJson(new DCGetTurnValuesAsJson(controller));
    controller->setGetScoresAsJson(new DCGetScoresAsJson(controller));
    controller->setUndoTurn(new DCUndoTurn(controller));
    controller->setRedoTurn(new DCRedoTurn(controller));
}
