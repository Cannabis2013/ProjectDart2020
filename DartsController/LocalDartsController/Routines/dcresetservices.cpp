#include "dcresetservices.h"

#include <DartsController/Contracts/ServicesProvider/dcservices.h>
#include <DartsController/Contracts/Meta/dcmetaservices.h>
#include <DartsController/Contracts/Index/dcindexservices.h>
#include <DartsController/Contracts/Players/dcplayersservices.h>
#include <DartsController/Contracts/Players/idcplayermanager.h>
#include <DartsController/Contracts/Models/dcmeta.h>
#include <DartsModelsContext/Contracts/abstractdartscontext.h>

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
