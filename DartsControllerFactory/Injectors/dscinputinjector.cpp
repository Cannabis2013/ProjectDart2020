#include "dscinputinjector.h"
#include "ServicesProvider/dcservices.h"
#include "DCInputServices/dcconvertinputs.h"
#include "DCInputServices/dcinputbuilder.h"
#include "DSCServices/dscinputadder.h"

void DSCInputInjector::inject(DCServices *dc)
{
    dc->setConvertInputs(new DCConvertInputs);
    dc->setInputConverter(new DCInputBuilder);
    dc->setInputAdder(new DSCInputAdder);

}
