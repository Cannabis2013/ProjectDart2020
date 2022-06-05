#include "dcresetservices.h"

#include <DartsController/ServicesProvider/dcservices.h>
#include <DartsController/Meta/dcmetaservices.h>
#include <DartsController/Index/dcindexservices.h>
#include <DartsController/Players/dcplayersservices.h>
#include <DartsController/Players/idcplayermanager.h>
#include <DartsController/Models/dcmeta.h>
#include <DartsModelsContext/SLAs/abstractdartscontext.h>

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
