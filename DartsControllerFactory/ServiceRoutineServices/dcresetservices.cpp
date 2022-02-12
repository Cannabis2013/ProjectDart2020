#include "dcresetservices.h"
#include "ServicesProvider/dcservices.h"
#include "Models/dcmeta.h"

void DCResetServices::reset()
{
    auto meta = _services->metaService()->meta();
    auto statusCode = _services->metaService()->Initialized;
    _services->indexController()->init(meta);
    _services->playerManager()->reset(meta.initRemScore);
    _services->metaService()->setMeta(statusCode);
}
