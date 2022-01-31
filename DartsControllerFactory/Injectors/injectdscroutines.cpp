#include "injectdscroutines.h"
#include "ServicesProvider/dcservices.h"
#include "DSCServices/dscinputevaluator.h"
#include "ModelsComCtxServices/dcupdatemodelscontext.h"
#include "DCInputServices/dcassembleinput.h"
#include "DCInputServices/dcexternalinputservice.h"
#include "PlayerStatsServices/dcupdatescorerange.h"
#include "DCTurnValuesServices/dccreateturnvalues.h"
#include "InitServices/dcinitializecontroller.h"
#include "ServiceRoutineServices/dcresetservices.h"

void InjectDSCRoutines::inject(DCServices *dc)
{
    injectInputRoutines(dc);
    injectStatsRoutines(dc);
    injectOtherRoutines(dc);
    dc->setTurnValuesBuilder(new DCCreateTurnValues(dc));
}

void InjectDSCRoutines::injectInputRoutines(DCServices *dc)
{
    dc->setInputEvaluator(new DSCInputEvaluator(dc));
    dc->setUpdateModelsContext(new DCUpdateModelsContext(dc));
    dc->setAssembleInput(new DCAssembleInput(dc));
    dc->setGetInputFromMdsService(new DCExternalInputService(dc));
}

void InjectDSCRoutines::injectStatsRoutines(DCServices *dc)
{
    dc->setUpdateInputStats(new DCUpdateScoreRange(dc));
}

void InjectDSCRoutines::injectOtherRoutines(DCServices *dc)
{
    dc->setInitializer(new DCInitializeController(dc));
    dc->setResetServices(new DCResetServices(dc));
}
