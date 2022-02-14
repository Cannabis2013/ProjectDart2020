#include "dcresetservices.h"
#include "ServicesProvider/dcservices.h"
#include "Models/dcmeta.h"

#include <SLAs/absdartsctx.h>

DCResetServices::DCResetServices(DCServices *services)
{
    _metaManager = services->metaServices()->metaManager();
    _indexController = services->indexServices()->indexController();
    _playerManager = services->playerServices()->playerManager();
    _modelsContext = services->modelsContext();
}

bool DCResetServices::reset()
{

    auto meta = _metaManager->meta();
    auto statusCode = _metaManager->Initialized;
    _indexController->init(meta);
    _playerManager->reset(meta.initRemScore);
    _metaManager->setStatus(statusCode);
    auto resetSuccess = _modelsContext->resetTournament(meta.tournamentID);
    return resetSuccess;
}
