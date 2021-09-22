#ifndef IDCRESETSCORESCOREMODELS_H
#define IDCRESETSCORESCOREMODELS_H

#include "idcinitialscore.h"
#include "idcscoresservice.h"

class IDCResetScoreScoreModels
{
public:
    virtual void reset(IDCScoresService *scoresService, const int &initialScore) const = 0;
};
#endif // IDCRESETSCORETUPLES_H
