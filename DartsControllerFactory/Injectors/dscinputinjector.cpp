#include "dscinputinjector.h"
#include "ServicesProvider/dcservices.h"
#include "DCInputServices/dcassembleinput.h"
#include "DCInputSLAs/dcinputsslas.h"
#include "DCInputServices/dcconvertinputs.h"
#include "DCInputServices/dcinputbuilder.h"
#include "DSCServices/dscinputadder.h"
#include "DSCServices/dscinputevaluator.h"
#include "ModelsComCtxServices/dcaddtomodelscontext.h"
#include "DCInputServices/dcgetinput.h"

void DSCInputInjector::inject(DCServices *dc)
{
    dc->setConvertInputs(new DCConvertInputs);
    dc->setInputConverter(new DCInputBuilder);
    dc->setInputAdder(new DSCInputAdder);
    dc->setInputEvaluator(new DSCInputEvaluator(dc));
    dc->setAddToModelsCtx(new DCAddToModelsContext(dc));
    dc->setAssembleInput(new DCAssembleInput(dc));
    dc->setGetInputFromMdsService(new DCGetInput(dc));
}
