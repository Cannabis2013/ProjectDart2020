#include "dcservices.h"
#include "Models/dcplayer.h"
#include "Models/dcinput.h"
#include "Models/dcmeta.h"
#include "SLAs/absdartsctx.h"
#include "DCIndexSLAs/idcindexconverter.h"
#include "PlayerStatsSLAs/idcstatistics.h"

void DCServices::updateServices(const DCInput &ipt)
{
    statisticsService()->update(ipt);
    playerService()->updateScore(ipt);
}
