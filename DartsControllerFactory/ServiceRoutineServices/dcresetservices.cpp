#include "dcresetservices.h"
#include "ServicesProvider/dcservices.h"
#include "Models/dcmeta.h"

void DCResetServices::reset()
{
    auto meta = _services->metaService()->meta();
    auto statusCode = _services->metaService()->Initialized;
    _services->indexService()->init(meta);
    _services->plaCtx()->reset(meta.initRemScore);
    _services->statisticsService()->reset();
    _services->metaService()->setMeta(statusCode);
}
