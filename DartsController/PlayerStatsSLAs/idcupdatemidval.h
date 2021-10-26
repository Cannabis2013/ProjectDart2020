#ifndef IDCUPDATEMIDVAL_H
#define IDCUPDATEMIDVAL_H
#include "DartsController/DCIndexSLAs/idcindexcontroller.h"
#include "DartsController/DCInputServices/dcinput.h"
#include "DartsController/DCScoresSLAs/idcscoremodels.h"
#include "DartsController/DCMetaSLAs/idcinitialscore.h"
#include "idcplayerstats.h"
class IDCUpdateMidVal
{
public:
    virtual void update(DCInput &input, const DCIndex &index, IDCPlayerStats *playerStatsContext,
                        const IDCInitialScore *initialScore) const = 0;
};
#endif // IDCUPDATEMIDVAL_H
