#include "dartsplayerinjector.h"
#include "SLAs/dartsmodelsservices.h"
#include "PlayerServices/dartsconvertplayer.h"

void DartsPlayerInjector::inject(DartsModelsServices *context) const
{
    auto plaServices = new DartsPlayerServices;
    plaServices->setPlayerConverter(new DartsConvertPlayer);
    context->setPlayerServices(plaServices);
}
