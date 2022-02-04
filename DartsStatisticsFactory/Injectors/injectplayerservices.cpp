#include "injectplayerservices.h"
#include "SLAs/servicesprovider.h"
#include "Players/playersdb.h"
#include "Players/jsontoplayer.h"
void InjectPlayerServices::inject(ServicesProvider *provider)
{
    auto services = new PlayerServices;
    services->setPlayersDb(new PlayersDb);
    services->setCreatePlayer(new JsonToPlayer);
    provider->setPlayerServices(services);
}
