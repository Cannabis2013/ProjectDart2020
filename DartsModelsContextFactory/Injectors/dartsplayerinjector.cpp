#include "dartsplayerinjector.h"
#include "SLAs/dmcservices.h"
#include "PlayerServices/dartsconvertplayer.h"

void DartsPlayerInjector::inject(DMCServices *context) const
{
    auto plaServices = new DartsPlayerServices;
    plaServices->setConvertPlayers(new DartsConvertPlayer);
    context->setPlayerServices(plaServices);
}
