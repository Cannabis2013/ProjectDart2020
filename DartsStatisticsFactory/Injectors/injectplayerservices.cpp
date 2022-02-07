#include "injectplayerservices.h"
#include "SLAs/servicescontext.h"
#include "Players/playersdb.h"
#include "Players/jsontoplayer.h"
void InjectPlayerServices::inject(ServicesContext *provider)
{
    auto services = new CurrentStatsServices;
    services->setPlayersDb(new PlayersDb);
    services->setCreatePlayer(new JsonToPlayer);
    provider->setPlayerServices(services);
}
