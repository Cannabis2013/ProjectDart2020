#include "dartsinputinjector.h"
#include "SLAs/dartsmodelsservices.h"
#include "InputSLAs/dartsinputservices.h"
#include "InputServices/countdartsinputs.h"
#include "InputServices/dartsdbinputstojson.h"
#include "InputServices/dartsinputbuilder.h"
#include "InputServices/dartsinputconverter.h"
#include "InputServices/dartsiptsdbctx.h"
#include "InputServices/getdartsinputs.h"
#include "InputServices/removedartsinputs.h"
#include "InputServices/sortdartsinputs.h"
#include "InputServices/sortdartsinputsbyindexes.h"
#include "InputServices/jsontodartsinputs.h"

void DartsInputInjector::injectServices(DartsModelsServices *context) const
{
    auto iptServices = new DartsInputServices;
    iptServices->setInputModelsToJson(new DartsDbInputsToJson);
    iptServices->setInputConverter(new DartsInputConverter);
    iptServices->setRemoveInputsFromDb(new RemoveDartsInputs);
    iptServices->setSortInputsByIndexes(new SortDartsInputsByIndexes);
    iptServices->setInputBuilder(new DartsInputBuilder);
    iptServices->setSortInputs(new SortDartsInputs);
    iptServices->setCountInputs(new CountDartsInputs);
    iptServices->setInputsDb(new DartsIptsDbCtx);
    iptServices->setGetInputsFromDb(new GetDartsInputs);
    iptServices->setJsonToInputs(new JsonToDartsInputs);
    context->setInputServices(iptServices);

}
