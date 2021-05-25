#include "playermodelsservicebuilder.h"

using namespace DartsModelsContext;

IPlayerModelsService *PlayerModelsServiceBuilder::buildModelsService() const
{
    auto localDb = PlayersJsonDb::createInstance(PlayerModelsJsonExtractor::createInstance(),
                                                 PlayerModelsJsonAssembler::createInstance());
    auto playerModelsService =
            LocalPlayerModelsService::createInstance()
            ->setModelDBContext(localDb);
    return playerModelsService;
}

