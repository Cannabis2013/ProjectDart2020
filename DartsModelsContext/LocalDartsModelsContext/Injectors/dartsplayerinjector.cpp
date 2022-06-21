#include "dartsplayerinjector.h"
#include <DartsModelsContext/Contracts/Player/DartsPlayerServices.h>
#include <DartsModelsContext/Contracts/dartsmodelsservices.h>
#include <DartsModelsContext/LocalDartsModelsContext/PlayerServices/dartsconvertplayer.h>

void DartsPlayerInjector::inject(DartsModelsServices *context) const
{
    auto plaServices = new DartsPlayerServices;
    plaServices->setPlayerConverter(new DartsConvertPlayer);
    context->setPlayerServices(plaServices);
}
