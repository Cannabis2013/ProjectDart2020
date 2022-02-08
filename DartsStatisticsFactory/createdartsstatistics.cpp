#include "createdartsstatistics.h"
#include "Injectors/injectplayerservices.h"
#include "Injectors/injectstatsroutines.h"
#include "Injectors/injectstatsservices.h"
#include "Injectors/createinputprovider.h"

IDartsStatistics *CreateDartsStatistics::create() const
{
    CreateInputProvider injectInputServices;
    InjectPlayerServices injectPlayerServices;
    InjectStatsServices _injectStatsServices;
    InjectStatsRoutines _injectRoutines;
}
