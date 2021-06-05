#include "playerjsonservicebuilder.h"

using namespace DartsModelsContext;

PlayerJsonServiceBuilder::ServiceInterface *DartsModelsContext::PlayerJsonServiceBuilder::buildModelsService() const
{
    auto service = PlayerModelsJsonService::createInstance()
            ->setGetPlayerIndexesFromJson(new GetPlayerIndexesFromJson)
            ->setAssembleJsonFromPlayerNamesAndIds(new JsonArrayFromPlayerNamesAndIds)
            ->setAssembleJsonFromPlayerIdAndName(new AssembleJsonFromPlayerNameAndId)
            ->setGetDeletePlayerIndexFromJson(new GetDeletePlayerIndexFromJson)
            ->setAssemblePlayerModelFromJson(new AssemblePlayerModelFromJson)
            ->setGetWinnerIdByJson(new GetWinnerIdByJson);
    return service;
}
