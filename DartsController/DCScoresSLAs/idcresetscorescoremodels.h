#ifndef IDCRESETSCORESCOREMODELS_H
#define IDCRESETSCORESCOREMODELS_H

#include "DartsController/DCMetaSLAs/idcinitialscore.h"
#include "DartsController/DCScoresSLAs/idcscoremodels.h"

class IDCResetScoreScoreModels
{
public:
    virtual void reset(IDCScoreModels *scoresService, const int &initialScore) const = 0;
};
#endif // IDCRESETSCORETUPLES_H
