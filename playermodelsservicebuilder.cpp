#include "playermodelsservicebuilder.h"

IPlayerModelsService *PlayerModelsServiceBuilder::buildModelsService() const
{
    auto localDb = PlayersJsonDb::createInstance(PlayerModelsJsonExtractor::createInstance(),
                                                 PlayerModelsJsonAssembler::createInstance());
    auto playerModelsService =
            LocalPlayerModelsService::createInstance()
            ->setModelDBContext(localDb);
    return playerModelsService;
}

