#include "dcresetservices.h"
#include "ServicesProvider/dcservices.h"
#include "Models/dcmeta.h"

DCResetServices::DCResetServices(DCServices *services)
{
    _metaManager = services->metaServices()->metaManager();
    _indexController = services->indexServices()->indexController();
    _playerManager = services->playerServices()->playerManager();
}

void DCResetServices::reset()
{

    auto meta = _metaManager->meta();
    auto statusCode = _metaManager->Initialized;
    _indexController->init(meta);
    _playerManager->reset(meta.initRemScore);
    _metaManager->setStatus(statusCode);
}
