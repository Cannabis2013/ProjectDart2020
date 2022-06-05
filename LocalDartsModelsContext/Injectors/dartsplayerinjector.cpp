#include "dartsplayerinjector.h"
#include <DartsModelsContext/ForeignContextSLAs/DartsPlayerServices.h>
#include <DartsModelsContext/SLAs/dartsmodelsservices.h>
#include <LocalDartsModelsContext/PlayerServices/dartsconvertplayer.h>

void DartsPlayerInjector::inject(DartsModelsServices *context) const
{
    auto plaServices = new DartsPlayerServices;
    plaServices->setPlayerConverter(new DartsConvertPlayer);
    context->setPlayerServices(plaServices);
}
