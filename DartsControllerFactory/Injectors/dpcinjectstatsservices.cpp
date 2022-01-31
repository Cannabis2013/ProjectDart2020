#include "dpcinjectstatsservices.h"
#include "ServicesProvider/dcservices.h"
#include "PlayerStatsSLAs/dcinputstatsslas.h"
#include "PlayerStatsServices/dcstatscontext.h"

void DPCInjectStatsServices::inject(DCServices *dc) const
{
    dc->setStatistics(new DCStatsContext);
}
