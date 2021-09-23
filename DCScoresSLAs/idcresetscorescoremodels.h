#ifndef IDCRESETSCORESCOREMODELS_H
#define IDCRESETSCORESCOREMODELS_H

#include "DCMetaSLAs/idcinitialscore.h"
#include "DCScoresSLAs/idcscoresservice.h"

class IDCResetScoreScoreModels
{
public:
    virtual void reset(IDCScoresService *scoresService, const int &initialScore) const = 0;
};
#endif // IDCRESETSCORETUPLES_H
