#include "dscstatsinjector.h"
#include "PlayerStatsSLAs/dcinputstatsslas.h"
#include "PlayerStatsServices/dcstatscontext.h"
#include "PlayerStatsServices/dscupdscorerng.h"

void DSCStatsInjector::inject(PlayerStatsSLAs *dc) const
{
    dc->setStatistics(new DCStatsContext);
    dc->setUpdateInputStats(new DSCUpdScoreRng);
}
