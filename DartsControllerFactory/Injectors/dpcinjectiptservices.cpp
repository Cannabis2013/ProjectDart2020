#include "dpcinjectiptservices.h"
#include "DCInputServices/dcassembleinput.h"
#include "ServicesProvider/dcservices.h"
#include "DCInputSLAs/dcinputsslas.h"
#include "DCInputServices/dcconvertinputs.h"
#include "DCInputServices/dcinputbuilder.h"
#include "ModelsComCtxServices/dcaddtomodelscontext.h"
#include "DPCServices/dpcinputadder.h"
#include "DPCServices/dpcinputevaluator.h"

void DPCInjectIptServices::inject(DCServices *dc) const
{
    dc->setConvertInputs(new DCConvertInputs);
    dc->setInputConverter(new DCInputBuilder);
    dc->setInputAdder(new DPCInputAdder);
    dc->setInputEvaluator(new DPCInputEvaluator);
    dc->setAddToModelsCtx(new DCAddToModelsContext(dc));
    dc->setAssembleInput(new DCAssembleInput(dc));
}
