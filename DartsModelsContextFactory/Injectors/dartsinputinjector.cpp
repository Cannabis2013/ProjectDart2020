#include "dartsinputinjector.h"
#include "InputSLAs/dartsiptslas.h"
#include "InputServices/countdartsinputs.h"
#include "InputServices/dartsdbinputstojson.h"
#include "InputServices/dartsinputbuilder.h"
#include "InputServices/dartsinputconverter.h"
#include "InputServices/dartsiptsdbctx.h"
#include "InputServices/getdartsinputs.h"
#include "InputServices/removedartsinputs.h"
#include "InputServices/sortdartsinputs.h"
#include "InputServices/sortdartsinputsbyindexes.h"
#include "InputServices/dartsinputstojson.h"
#include "InputServices/jsontodartsinputs.h"
#include "InputServices/dartssetipthint.h"
void DartsInputInjector::injectServices(DartsIptSLAs *context) const
{

    context->setCreateJsonFromInputs(new DartsInputsToJson);
    context->setInputModelsToJson(new DartsDbInputsToJson);
    context->setInputConverter(new DartsInputConverter);
    context->setRemoveInputsFromDb(new RemoveDartsInputs);
    context->setSortInputsByIndexes(new SortDartsInputsByIndexes);
    context->setInputBuilder(new DartsInputBuilder);
    context->setSortInputs(new SortDartsInputs);
    context->setCountInputs(new CountDartsInputs);
    context->setInputsDb(new DartsIptsDbCtx);
    context->setGetInputsFromDb(new GetDartsInputs);
    context->setJsonToInputs(new JsonToDartsInputs);
    context->setSetInputHint(new DartsSetIptHint);
}
