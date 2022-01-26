#include "dpcinjectstatsservices.h"
#include "PlayerStatsSLAs/dcinputstatsslas.h"
#include "PlayerStatsServices/dcstatscontext.h"
#include "PlayerStatsServices/dpcupdatescorerange.h"

void DPCInjectStatsServices::inject(DCServices *dc) const
{
    dc->setStatistics(new DCStatsContext);
    dc->setUpdateInputStats(new DPCUpdateScoreRange(dc));
}
