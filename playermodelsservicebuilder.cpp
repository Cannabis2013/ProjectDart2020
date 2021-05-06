#include "playermodelsservicebuilder.h"

IPlayerModelsService<IPlayerModel<QUuid, QString> > *PlayerModelsServiceBuilder::buildModelsService() const
{
    auto playerModelsService =
            LocalPlayerModelsService::createInstance()
            ->setModelDBContext(new PlayersJsonDb);
    return playerModelsService;
}

