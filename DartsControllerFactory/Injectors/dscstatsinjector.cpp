#include "dscstatsinjector.h"
#include "PlayerStatsSLAs/dcinputstatsslas.h"
#include "PlayerStatsServices/dcstatscontext.h"
#include "ServicesProvider/dcservices.h"

void DSCStatsInjector::inject(DCServices *dc) const
{
    dc->setStatistics(new DCStatsContext);
}
