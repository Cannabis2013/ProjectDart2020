#include "dscjsonresponseinjector.h"
#include "DCJsonSLAs/dcjsonslas.h"
#include "DCJsonServices/dcjsonbuilder.h"
#include "DCInputServices/dcinputjsonbuilder.h"
#include "DCScoresServices/dcscorejsonbuilder.h"
#include "DCIndexServices/dcidxjsonbuilder.h"
#include "DCIndexServices/dcreqidxjsonbuilder.h"
#include "DCMetaServices/DCMetaInfoJsonBuilder.h"
#include "DCTurnValuesServices/DCTurnValuesJsonBuilder.h"

void DSCJsonResponseInjector::inject(DCJsonSLAs *dc)
{
    auto builder = new DCJsonBuilder;
    injectBuilder(builder);
    dc->setJsonResponseBuilder(builder);
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
