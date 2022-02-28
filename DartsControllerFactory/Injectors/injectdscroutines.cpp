#include "injectdscroutines.h"
#include "ServicesProvider/dcservices.h"
#include "Routines/dcaddinput.h"
#include "Init/dcinitialize.h"
#include "Routines/dcresetservices.h"
#include "Routines/dccreatewinnerreport.h"
#include "Routines/dcgetturnvaluesasjson.h"
#include "Routines/dcgetscoresasjson.h"
#include "Routines/dcundoturn.h"
#include "Routines/dcredoturn.h"

#include <Controller/dartscontroller.h>

void InjectDSCRoutines::inject(DartsController *controller)
{
    controller->setInitializer(new DCInitialize(controller));
    controller->setResetServices(new DCResetServices(controller));
    controller->setUpdateModelsContext(new DCAddInput(controller));
    controller->setCreateWinnerReport(new DCCreateWinnerReport(controller));
    controller->setGetTurnValuesAsJson(new DCGetTurnValuesAsJson(controller));
    controller->setGetScoresAsJson(new DCGetScoresAsJson(controller));
    controller->setUndoTurn(new DCUndoTurn(controller));
    controller->setRedoTurn(new DCRedoTurn(controller));
}
