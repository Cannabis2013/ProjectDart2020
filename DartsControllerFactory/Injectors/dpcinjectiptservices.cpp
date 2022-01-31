#include "dpcinjectiptservices.h"
#include "ServicesProvider/dcservices.h"
#include "DCInputSLAs/dcinputsslas.h"
#include "DCInputServices/dcconvertinputs.h"
#include "DCInputServices/dcinputbuilder.h"
#include "DPCServices/dpcinputadder.h"
void DPCInjectIptServices::inject(DCServices *dc) const
{
    dc->setConvertInputs(new DCConvertInputs);
    dc->setInputConverter(new DCInputBuilder);
    dc->setInputAdder(new DPCInputAdder);
}
