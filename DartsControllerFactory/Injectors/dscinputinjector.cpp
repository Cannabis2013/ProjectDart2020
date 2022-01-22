#include "dscinputinjector.h"

#include "DCInputSLAs/dcinputsslas.h"
#include "DCInputServices/dcconvertinputs.h"
#include "DCInputServices/dcinputbuilder.h"
#include "DSCServices/dscinputadder.h"
#include "DSCServices/dscinputevaluator.h"
#include "ModelsComCtxServices/dcaddtomodelcontext.h"

void DSCInputInjector::inject(DCInputsSLAs *dc)
{
    dc->setConvertInputs(new DCConvertInputs);
    dc->setInputConverter(new DCInputBuilder);
    dc->setInputEvaluator(new DSCInputEvaluator);
    dc->setCreateInput(new DSCInputAdder);
    dc->setAddToModelsCtx(new DCAddToModelsContext());
}
