#include "dscjsonresponseinjector.h"
#include "DCJsonSLAs/dcjsonservices.h"
#include "DCJsonServices/dcjsonbuilder.h"
#include "DCInputServices/dcinputjsonbuilder.h"
#include "DCScoresServices/dcscorejsonbuilder.h"
#include "DCIndexServices/dcidxjsonbuilder.h"
#include "DCIndexServices/dcreqidxjsonbuilder.h"
#include "DCMetaServices/DCMetaInfoJsonBuilder.h"
#include "DCTurnValuesServices/DCTurnValuesJsonBuilder.h"
#include "ServicesProvider/dcservices.h"

void DSCJsonResponseInjector::inject(DCServices *dc)
{
    auto jsonServices = new DCJsonServices;
    auto builder = new DCJsonBuilder;
    injectBuilder(builder);
    jsonServices->setJsonResponseBuilder(builder);
    dc->setJsonServices(jsonServices);
}

void DSCJsonResponseInjector::injectBuilder(AbstractDCJsonBuilder *builder) const
{
    builder->setInputJsonBuilder(new DCInputJsonBuilder);
    builder->setScoreModelJsonBuilder(new DCScoreJsonBuilder);
    builder->setIdxJsonBuilder(new DCIdxJsonBuilder);
    builder->setReqIdxJsonBuilder(new DCReqIdxJsonBuilder);
    builder->setMetaJsonBuilder(new DCMetaInfoJsonBuilder);
    builder->setTurnValuesJsonBuilder(new DCTurnValuesJsonBuilder);
}
